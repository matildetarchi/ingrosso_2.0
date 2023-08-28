//
// Created by dario on 15/06/2023.
//

#include "dbStoreManager.h"

#include <utility>

dbStoreManager::dbStoreManager(shared_ptr<Database> d) {
    db = d->get_db();
    prod=make_shared<Product>();
}



void dbStoreManager::change_data(int index, const string& desc_prod, double price, int available_quantity){

    //metodo per cambiare i valori di un prodotto del proprio magazzino
    //lancio la query
    string query = "UPDATE store SET desc_prod = '"+ desc_prod +"', price_product ='"+ to_string(price) +"', available_quantity ='"+to_string(available_quantity)+"' WHERE id = '"+to_string(index)+"'";
    db->exec(query);

    string query_id = "SELECT id FROM store WHERE id = '"+to_string(index)+"'";
    int id = db->execAndGet(query_id).getInt();

    vector<std::shared_ptr<Product>> prod_list;
    prod_list = st->get_products();
    prod = prod_list[id];

    prod->set_desc(desc_prod);
    prod->set_price(price);
    prod->set_available_quantity(available_quantity);
}

void dbStoreManager::add_to_db() {

    //metodo per aggiungere un nuovo prodotto al magazzino
    int index = st->get_num_prod()-1;
    //prendo l'id della sottocategoria alla quale appartiene il prodotto
    vector<std::shared_ptr<Product>> prod_list;
    prod_list = st->get_products();
    prod = prod_list[index];
    string query_sub = "SELECT id FROM subcategories WHERE name='"+prod->get_subcategory()+"'";
    int id_sub = db->execAndGet(query_sub);

    //prendo l'id del fornitore proprietario di questo prodotto
    string query_prov = "SELECT id FROM users WHERE username = '"+st->get_prov()+"'";
    int id_prov = db->execAndGet(query_prov).getInt();

    //prendo il massimo id dei prodotti che ha il fornitore nel suo magazzino
    string query_id_inter = "SELECT MAX(id) FROM store WHERE id_prov ='"+ to_string(id_prov)+"'";
    int id_intern = db->execAndGet(query_id_inter).getInt();

    //lancio la query di inserimento nel db
    string query_insert = "INSERT INTO store (available_quantity, price_product, desc_prod, id_sub, id_prov, id_intern) VALUES"
                          " ('"+to_string(prod->get_quantity())+ "', '" + to_string(prod->get_price()) + "', '"+prod->get_desc()+"', '"+to_string(id_sub)+"', '"+to_string(id_prov)+"', '"+to_string(id_intern+1)+"');";
    db->exec(query_insert);

}

bool dbStoreManager::remove_from_db(int id_intern)  {

    //metodo che permette a un fornitore di togliere un prodotto dal suo magazzino

    //controllo che il prodotto in questione non sia all'interno
    // della lista dei preferiti di qualche utente
    //in caso sia presente lo elimino

    string query_count_in_fav = "SELECT count(*) FROM favourites WHERE id_store ='"+ to_string(id_intern)+"'";
    int count_fav = db->execAndGet(query_count_in_fav);
    if (count_fav>0) {
        fav->remove_prod(id_intern);
    }

    //controllo che il prodotto non sia presente in qualche ordine in sopeso
    //in caso sia presente ritorno 0
    //non permettendo all'utente di cancellare il prodotto
    string query_count_in_ord = "SELECT count(*) FROM orders, orders_details WHERE id_order = orders_details.id AND id_product = '"+ to_string(id_intern)+"' AND status ='S'";
    int count_orders = db->execAndGet(query_count_in_ord);
    if (count_orders>0) {
        return false;
    }

    //controllo che il prodotto non sia all'interno del carrello di qualche utente
    //in caso sia presente ritorno 0
    //non permetteno all'utente di cancellare il prodotto
    string query_count_in_cart = "SELECT count(*) FROM cart WHERE id_store ='"+ to_string(id_intern)+"'";
    int count_cart = db->execAndGet(query_count_in_cart);
    if (count_cart>0) {
        cart->remove_prod(id_intern);
    }

    //se il prodotto non è presente da nessuna parte
    //lo elimino da tutti gli ordini già accettati o rifiutati
    //per evitare futuri conflitti tra le tabelle

    //TODO cancellare anche da orders_details tramite ciclo
    string query_del_from_ord = "DELETE FROM orders WHERE id_product = "+ to_string(id_intern)+"";
    db->exec(query_del_from_ord);

    //se il prodotto non è presente da nessuna parte
    //lancio la query delete e ritorno 1
    string query = "DELETE FROM store WHERE id = '"+ to_string(id_intern)+"'";
    db->exec(query);
    st->remove_one(id_intern);
    return true;

}

vector<vector<string>> dbStoreManager::select_for_client(const string &sub_name, const string &disp, const string &order) {

    //metodo per seleziona tutti i prodotti dai vari magazzini
    //appartenenti a una determinata sottocategoria

    //prendo l'id della sottocategoria della quale si vuole vedere i prodotti
    string query_sub = "SELECT id FROM subcategories WHERE name ='"+sub_name+"'";
    int i = db->execAndGet(query_sub).getInt();

    //creo la matrice che conterrà i valori
    vector<vector<string>> mat;

    //controllo il tipo di disponibilità
    //della quale l'utente vuole vedere i prodotti
    //solo disponibili o tutti quanti
    int n_dispo;
    if (disp=="Only Available") {
        n_dispo = 1;
    } else {
        n_dispo = 0;
    }

    //controllo i tipo di ordinamento che l'utente
    //vuole usare per vedere i prodotti
    string str_order;
    if (order=="Name Product") {
        str_order="desc_prod;";
    } else if (order=="Price") {
        str_order="price_product;";
    } else if (order=="Provider Name"){
        str_order="username;";
    } else {
        str_order=order;
    }

    //lancio la query
    //popolo la matrice
    //restituisco la matrice
    string select = "SELECT desc_prod, price_product, username, CASE WHEN (available_quantity>0) THEN 'Available ('||available_quantity||')' "
                    "ELSE 'Not Available' END,store.id FROM users,store WHERE id_prov=users.id AND id_sub='"+to_string(i)+"' AND "
                                                                                                                          "available_quantity>= '"+ to_string(n_dispo)+"' ORDER BY '"+str_order+"';";

    SQLite::Statement query(*db,select);
    vector<string> vector;
    string data;
    int m=0;
    int n=0;
    while (query.executeStep()){
        while (n<5) {
            data=query.getColumn(n).getText();
            vector.push_back(data);
            n++;
        }
        mat.push_back(vector);
        vector.clear();
        n=0;
        m++;
    }
    return mat;

}


int dbStoreManager::select_count_for_client(const string &sub_name, const string &disp) {

    //metodo per sapere quanti prodotti ci sono
    //di una determinata sottocategoria e disponibilità

    //prendo l'id della sottocategoria della quale si vuole vedere i prodotti
    string query_sub = "SELECT id FROM subcategories WHERE name='"+sub_name+"'";
    int i = db->execAndGet(query_sub).getInt();

    //controllo il tipo di disponibilità
    //della quale l'utente vuole vedere i prodotti
    //solo disponibili o tutti quanti
    int n_dispo;
    if (disp=="Only Available") {
        n_dispo = 1;
    } else {
        n_dispo = 0;
    }

    //lancio la query e restituisco il valore
    string query_select_count = "SELECT count(*) FROM store WHERE id_sub = '"+ to_string(i)+"' AND available_quantity>= '"+to_string(n_dispo)+"'";
    int count = db->execAndGet(query_select_count).getInt();
    return count;

}

void dbStoreManager::select_for_prov() {
    string username=user->get_username();
    st= make_shared<Store>(username);
    //metodo che prende i valori dei prodotti nel magazzino di un fornitore

    //seleziono l'id del fornitore che sta usando il programma
    int id_prov = user->get_db_id();

    //prendo la quantità di prodotti presenti
    string query_select_count = "SELECT count(*) FROM store WHERE id_prov ='"+ to_string(id_prov)+"'";
    int count = db->execAndGet(query_select_count).getInt();


    //lancio la query
    //popolo la matrice
    //restituisco la matrice
    if(count > 0) {
        string select = "SELECT desc_prod, price_product, available_quantity, subcategories.name, store.id FROM store,subcategories WHERE id_sub =subcategories.id AND id_prov= '" +
                        to_string(id_prov) + "';";
        SQLite::Statement query(*db,select);


        while (query.executeStep()) {
            string desc_prod = query.getColumn(0).getText();
            double price = query.getColumn(1).getDouble();
            int quantity = query.getColumn(2);
            string subcategory = query.getColumn(3).getText();
            int id_store = query.getColumn(4);
            prod->set_available_quantity(quantity);
            prod->set_price(price);
            prod->set_desc(desc_prod);
            prod->set_subcategory(subcategory);
            prod->set_username_prov(username);
            prod->set_quantity(0);
            prod->set_id_store(id_store);
            st->add_to_store(prod);
        }

    }

}

int dbStoreManager::select_count_for_provider(){

    //seleziono l'id del fornitore che sta usando il programma
    int id_prov = user->get_db_id();

    //prendo la quantità di prodotti presenti
    string query_select_count = "SELECT count(*) FROM store WHERE id_prov ='"+ to_string(id_prov)+"'";
    int count = db->execAndGet(query_select_count).getInt();
    return count;

}

shared_ptr<Product> dbStoreManager::select_prod_to_modify(int id_prod){
    if(user->get_type()=="F") {
        int id_prov = user->get_db_id();
        string username= user->get_username();
        string select_prod = "SELECT desc_prod, price_product, available_quantity, subcategories.name FROM store,subcategories WHERE id_sub =subcategories.id AND id_prov= '" +
                                                         to_string(id_prov) +"' AND store.id = '" + to_string(id_prod) + "' ";
        SQLite::Statement query_prod(*db,select_prod);
        query_prod.exec();
        string desc_prod = query_prod.getColumn(0).getText();
        double price = query_prod.getColumn(1).getDouble();
        int available_quantity = query_prod.getColumn(2);
        string subcategory = query_prod.getColumn(3).getText();

        prod->set_available_quantity(available_quantity);
        prod->set_price(price);
        prod->set_desc(desc_prod);
        prod->set_subcategory(subcategory);
        prod->set_username_prov(username);
        prod->set_quantity(0);
        prod->set_id_store(id_prod);
        return prod;
    }else
        throw std::runtime_error("Errore, l'utente selezionato non è un fornitore");

}