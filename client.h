//
// Created by Matilde Tarchi on 16/06/23.
//

#ifndef INGROSSO_ONLINE_CLIENT_H
#define INGROSSO_ONLINE_CLIENT_H

#include "user.h"
#include "OrdersList.h"
#include "favourites.h"
#include "cart.h"


class Client:public User {
public:
    Client();
    Client( const std::string &t, const std::string &bn,const std::string &a, const std::string &e, const std::string &password, const std::string &us, const std::string &c);
    ~Client() override;

    Orders *getOrder(){
        return order;
    };
    Favourites *getFavorites(){
        return fav;
    };
    Cart *getCart(){
        return cart;
    };

    void setOrder(Orders *ord) override;
    void setFavourites(Favourites *f) override;
    void setCart(Cart *crt) override;

private:
    Orders *order;
    Favourites *fav;
    Cart *cart;
};


#endif //INGROSSO_ONLINE_CLIENT_H
