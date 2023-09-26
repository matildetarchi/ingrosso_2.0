//
// Created by dario on 15/06/2023.
//

#include "dbStoreManager.h"


dbStoreManager::dbStoreManager(const shared_ptr<Database>& d) {
    db = d->get_db();
    prod=make_shared<Product>();
}



void dbStoreManager::change_data(int index, const string& desc_prod, double price, int available_quantity){
    //metodo per cambiare i valori di un prodotto del proprio magazzino
    //lancio la query
    string query = "UPDATE store SET desc_prod = '"+ desc_prod +"', price_product ='"+ to_string(price) +"', available_quantity ='"+to_string(available_quantity)+"' WHERE id = '"+to_string(index)+"'";
    db->exec(query);
}

void dbStoreManager::add_to_db() {
     st = prov->get_store();
    //metodo per aggiungere un nuovo prodotto al magazzino
    int index = st->get_num_prod()-1;
    //prendo l'id della sottocategoria alla quale appartiene il prodotto

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

    //lancio la query d'inserimento nel db
    string query_insert = "INSERT INTO store (available_quantity, price_product, desc_prod, id_sub, id_prov) VALUES"
                          " ('"+to_string(prod->get_q_available())+ "', '" + to_string(prod->get_price()) + "', '"+prod->get_desc()+"', '"+to_string(id_sub)+"', '"+to_string(id_prov)+"');";
    db->exec(query_insert);

}

bool dbStoreManager::remove_from_db(int id_intern)  {

    //metodo che permette a un fornitore di togliere un prodotto dal suo magazzino

    //controllo che il prodotto in questione non sia all'interno
    // della lista dei preferiti di qualche utente
    //in caso sia presente lo elimino

    string query_count_in_fav = "DELETE FROM favourites WHERE id_store ='"+ to_string(id_intern)+"'";
    db->exec(query_count_in_fav);


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
    string query_count_in_cart = "DELETE FROM cart WHERE id_store ='"+ to_string(id_intern)+"'";
    db->exec(query_count_in_cart);

    //se il prodotto non è presente da nessuna parte
    //lo elimino da tutti gli ordini già accettati o rifiutati
    //per evitare futuri conflitti tra le tabelle


    string query_del_from_ord = "DELETE FROM orders_details WHERE id_product = "+ to_string(id_intern)+"";
    db->exec(query_del_from_ord);

    //se il prodotto non è presente da nessuna parte
    //lancio la query delete e ritorno 1
    string query = "DELETE FROM store WHERE id = '"+ to_string(id_intern)+"'";
    db->exec(query);
    st->remove_one(id_intern);
    return true;

}

vector<shared_ptr<Product>> dbStoreManager::select_for_client(const string &sub_name, const string &disp) {

    //metodo per seleziona tutti i prodotti dai vari magazzini
    //appartenenti a una determinata sottocategoria

    //prendo l'id della sottocategoria della quale si vuole vedere i prodotti
    string query_sub = "SELECT id FROM subcategories WHERE name ='" + sub_name + "'";
    int i = db->execAndGet(query_sub).getInt();


    //controllo il tipo di disponibilità
    //della quale l'utente vuole vedere i prodotti
    //solo disponibili o tutti quanti
    int n_dispo = 0;
    if (disp == "Only Available") {
        n_dispo = 1;
    } else {
        n_dispo = 0;
    }
    //prendo la quantità di prodotti presenti
    string query_select_count = "SELECT count(*) FROM users,store WHERE id_prov=users.id AND id_sub='" + to_string(i) +"' AND available_quantity>= '" + to_string(n_dispo) + "'";
    int count = db->execAndGet(query_select_count).getInt();

    vector<shared_ptr<Product>> product_list;
    //lancio la query
    //popolo la matrice
    //restituisco la matrice
    if (count > 0) {
        //lancio la query

        string select =
                "SELECT desc_prod, price_product, username, store.id, available_quantity FROM users,store WHERE id_prov=users.id AND id_sub='" +
                to_string(i) + "' AND available_quantity>= '" + to_string(n_dispo) + "'";

        SQLite::Statement query(*db, select);

        while (query.executeStep()) {
            string desc_prod = query.getColumn(0).getText();
            double price = query.getColumn(1).getDouble();
            string username_prov = query.getColumn(2).getText();
            int id_store = query.getColumn(3);
            int a_quantity = query.getColumn(4);

            shared_ptr<Product> product = make_shared<Product>(desc_prod, price, 0, a_quantity, username_prov,
                                                               sub_name);
            product->set_id_store(id_store);
            product_list.push_back(product);

        }

    }
    return product_list;
}

int dbStoreManager::select_count_for_client(const string &sub_name, const string &disp) {

    //metodo per sapere quanti prodotti ci sono
    //di una determinata sottocategoria e disponibilità

    //prendo l'id della sottocategoria della quale si vuole vedere i prodotti
    string query_sub = "SELECT id FROM subcategories WHERE name='" + sub_name + "'";
    int i = db->execAndGet(query_sub).getInt();

    //controllo il tipo di disponibilità
    //della quale l'utente vuole vedere i prodotti
    //solo disponibili o tutti quanti
    int n_dispo;
    if (disp == "Only Available") {
        n_dispo = 1;
    } else {
        n_dispo = 0;
    }

    //lancio la query e restituisco il valore
    string query_select_count = "SELECT count(*) FROM store WHERE id_sub = '" + to_string(i) + "' AND available_quantity>= '" +
            to_string(n_dispo) + "'";
    int count = db->execAndGet(query_select_count).getInt();

    return count;
}

void dbStoreManager::select_for_prov() {

    string username = prov->get_username();

    //metodo che prende i valori dei prodotti nel magazzino di un fornitore

    //seleziono l'id del fornitore che sta usando il programma
    int id_prov = prov->get_db_id();

    //prendo la quantità di prodotti presenti
    string query_select_count = "SELECT count(*) FROM store WHERE id_prov ='" + to_string(id_prov) + "'";
    int count = db->execAndGet(query_select_count).getInt();


    //lancio la query
    //popolo la matrice
    //restituisco la matrice
    if (count > 0) {
        string select = "SELECT desc_prod, price_product, available_quantity, subcategories.name, store.id FROM store,subcategories WHERE id_sub =subcategories.id AND id_prov= '" +
                to_string(id_prov) + "';";
        SQLite::Statement query(*db, select);


        while (query.executeStep()) {
            string desc_prod = query.getColumn(0).getText();
            double price = query.getColumn(1).getDouble();
            int quantity = query.getColumn(2);
            string subcategory = query.getColumn(3).getText();
            int id_store = query.getColumn(4);

            shared_ptr<Product> product = make_shared<Product>(desc_prod, price, 0, quantity, username, subcategory);
            product->set_id_store(id_store);

            st->add_to_store(product);
        }

    }

}

int dbStoreManager::select_count_for_provider() {

    //seleziono l'id del fornitore che sta usando il programma
    int id_prov = prov->get_db_id();

    //prendo la quantità di prodotti presenti
    string query_select_count = "SELECT count(*) FROM store WHERE id_prov ='" + to_string(id_prov) + "'";
    int count = db->execAndGet(query_select_count).getInt();
    return count;

}

shared_ptr<Product> dbStoreManager::select_prod_to_modify(int id_prod) {

    int id_prov = prov->get_db_id();
    string username = prov->get_username();
    string select_prod = "SELECT desc_prod, price_product, available_quantity, subcategories.name FROM store,subcategories WHERE id_sub =subcategories.id AND id_prov= " +
            to_string(id_prov) + " AND store.id = " + to_string(id_prod) + " ";
    SQLite::Statement query_prod(*db, select_prod);
    while(query_prod.executeStep()) {
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
    }
    return prod;
}