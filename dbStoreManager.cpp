//
// Created by dario on 15/06/2023.
//

#include "dbStoreManager.h"

void dbStoreManager::changeData(int index, const string &desc_prod, double price, int quantity){

    //metodo per cambiare i valori di un prodotto del proprio magazzino

    //lancio la query
    string query="UPDATE store SET desc_prod = '"+ desc_prod +"', price_product="+ to_string(price) +", available_quantity="+to_string(quantity)+" WHERE id = "+to_string(index)+"";
    db.exec(query);

    store.set_desc_prod(index,desc_prod);
    store.set_price(index,price);
    store.set_quantity(index,quantity);
}

void dbStoreManager::add_to_db(Store *store) {

    //metodo per aggiungere un nuovo prodotto al magazzino
    int index=store->get_num_prod()-1;
    //prendo l'id della sottocategoria alla quale appartiene il prodotto
    string query_sub="SELECT id FROM subcategories WHERE name='"+store->get_prod(index)+"'";
    int id_sub=db.execAndGet(query_sub);

    //prendo l'id del fornitore proprietario di questo prodotto
    string query_prov="SELECT id FROM users WHERE username = '"+store->get_prov()+"'";
    int id_prov=db.execAndGet(query_prov).getInt();

    //prendo il massimo id dei prodotti che ha il fornitore nel suo magazzino
    std::string query_id_inter="SELECT MAX(id_intern) FROM store WHERE id_prov="+ to_string(id_prov)+"";
    int id_intern=db.execAndGet(query_id_inter).getInt();

    //lancio la query di inserimento nel db
    string query_insert="INSERT INTO store (available_quantity, price_product, desc_prod,id_sub, id_prov, id_intern) VALUES (" +
                        to_string(store->get_quantity(index))+ ", " + to_string(store->get_price(index)) + ", '"+store->get_desc(index)+"', "+to_string(id_sub)+", "+to_string(id_prov)+", "+to_string(id_intern+1)+");";
    db.exec(query_insert);

}

bool dbStoreManager::remove_from_db(int id_store)  {

    //metodo che permette a un fornitore di togliere un prodotto dal suo magazzino

    //controllo che il prodotto in questione non sia all'interno
    // della lista dei preferiti di qualche utente
    //in caso sia presente ritorno 0
    //non permettendo all'utente di cancellare il prodotto
    string query_count_in_fav="SELECT count(*) FROM favourites WHERE id_store="+ to_string(id_store)+"";
    int count_fav=db.execAndGet(query_count_in_fav);
    if (count_fav>0) {
        return false;
    }

    //controllo che il prodotto non sia presente in qualche ordine in sopeso
    //in caso sia presente ritorno 0
    //non permettendo all'utente di cancellare il prodotto
    string query_count_in_ord="SELECT count(*) FROM orders WHERE id_store="+ to_string(id_store)+" AND status='S'";
    int count_orders=db.execAndGet(query_count_in_ord);
    if (count_orders>0) {
        return false;
    }

    //controllo che il prodotto non sia all'interno del carrello di qualche utente
    //in caso sia presente ritorno 0
    //non permetteno all'utente di cancellare il prodotto
    string query_count_in_cart="SELECT count(*) FROM cart WHERE id_store="+ to_string(id_store)+"";
    int count_cart=db.execAndGet(query_count_in_cart);
    if (count_cart>0) {
        return false;
    }

    //se il prodotto non è presente da nessuna parte
    //lo elimino da tutti gli ordini già accettati o rifiutati
    //per evitare futuri conflitti tra le tabelle
    string query_del_from_ord="DELETE FROM orders WHERE id_store = "+ to_string(id_store)+"";
    db.exec(query_del_from_ord);

    //se il prodotto non è presente da nessuna parte
    //lancio la query delete e ritorno 1
    string query="DELETE FROM store WHERE id = "+ to_string(id_store)+"";
    db.exec(query);
    store.remove_one(id_store);
    return true;

}

vector<vector<string>> dbStoreManager::select_for_client(const string &sub_name, const string &disp, const string &order) {

    //metodo per seleziona tutti i prodotti dai vari magazzini
    //appartenenti a una determinata sottocategoria

    //prendo l'id della sottocategoria della quale si vuole vedere i prodotti
    string query_sub="SELECT id FROM subcategories WHERE name='"+sub_name+"'";
    int i = db.execAndGet(query_sub).getInt();

    //creo la matrice che conterrà i valori
    vector<vector<string>> mat;

    //controllo il tipo di disponibilità
    //della quale l'utente vuole vedere i prodotti
    //solo disponibili o tutti quanti
    int n_disp;
    if (disp=="Only Available") {
        n_disp=1;
    } else {
        n_disp=0;
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
    string select="SELECT desc_prod, price_product, username, CASE WHEN (available_quantity>0) THEN 'Available ('||available_quantity||')' ELSE 'Not Available' END,store.id FROM users,store WHERE id_prov=users.id AND id_sub="+
                  to_string(i)+" AND available_quantity>="+ to_string(n_disp)+" ORDER BY "+str_order+";";

    SQLite::Statement query(db,select);
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
    string query_sub="SELECT id FROM subcategories WHERE name='"+sub_name+"'";
    int i = db.execAndGet(query_sub).getInt();

    //controllo il tipo di disponibilità
    //della quale l'utente vuole vedere i prodotti
    //solo disponibili o tutti quanti
    int n_disp;
    if (disp=="Only Available") {
        n_disp=1;
    } else {
        n_disp=0;
    }

    //lancio la query e restituisco il valore
    string query_select_count="SELECT count(*) FROM store WHERE id_sub ="+ to_string(i)+" AND available_quantity>="+to_string(n_disp)+"";
    int count = db.execAndGet(query_select_count).getInt();
    return count;

}

void dbStoreManager::select_for_prov(const string &username) {

    //metodo che prende i valori dei prodotti nel magazzino di un fornitore

    //seleziono l'id del fornitore che sta usando il programma
    string query_select_prov="SELECT id FROM users WHERE username='"+username+"'";
    int id_prov=db.execAndGet(query_select_prov).getInt();

    //prendo la quantità di prodotti presenti
    string query_select_count="SELECT count(*) FROM store WHERE id_prov ="+ to_string(id_prov)+"";
    int count = db.execAndGet(query_select_count).getInt();


    //lancio la query
    //popolo la matrice
    //restituisco la matrice
    string select = "SELECT desc_prod, price_product, available_quantity,subcategories.name FROM store,subcategories WHERE id_sub=subcategories.id AND id_prov=" +
                    to_string(id_prov) + ";";
    SQLite::Statement query(db,select);



    while (query.executeStep()) {
        string desc_prod = query.getColumn(0).getText();
        double price = query.getColumn(1).getDouble();
        int quantity = query.getColumn(2).getInt();
        string subcategory= query.getColumn(3).getText();

        Store *store1 =new Store(quantity,subcategory,price,desc_prod,username);
    }

}