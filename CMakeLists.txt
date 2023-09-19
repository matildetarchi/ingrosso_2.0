cmake_minimum_required(VERSION 3.21)
project(ingrosso_online)

set(CMAKE_CXX_STANDARD 17)

enable_testing()
add_subdirectory(test)
add_subdirectory(SQLiteCpp)

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /CLionProjects/ingrosso/SQLiteCpp)
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} /CLionProjects/ingrosso/SQLiteCpp/include)


include_directories(SQLiteCpp/sqlite3)
include_directories(SQLiteCpp/include)
find_package(wxWidgets REQUIRED net gl core base media)
include(${wxWidgets_USE_FILE})


set (SOURCE_FILES Cart.cpp Cart.h CartPage.cpp CartPage.h ChooseStatusPage.cpp ChooseStatusPage.h Client.cpp Client.h Database.cpp Database.h Date.cpp Date.h dbCartManager.cpp dbCartManager.h dbCategoriesManager.cpp dbCategoriesManager.h dbCityManager.cpp dbCityManager.h dbFavouritesManager.cpp dbFavouritesManager.h dbOrdersManager.cpp dbOrdersManager.h dbStoreManager.h dbStoreManager.cpp dbSubcategoriesManager.cpp dbSubcategoriesManager.h dbUserManager.cpp dbUserManager.h Engine.cpp Engine.h Favourites.cpp Favourites.h FavouritesListPage.cpp FavouritesListPage.h ForgotPasswordPage.cpp ForgotPasswordPage.h HomePageClient.cpp HomePageClient.h HomePageProviders.cpp HomePageProviders.h InitialPage.cpp InitialPage.h InsertProductPage.cpp InsertProductPage.h LogInPage.cpp LogInPage.h  main.cpp ManageProfilePage.cpp ManageProfilePage.h ManageRequestPage.cpp ManageRequestPage.h ModifyProductPage.cpp ModifyProductPage.h MyApp.cpp MyApp.h Order.cpp Order.h OrderHistoryForClientPage.cpp OrderHistoryForClientPage.h OrdersList.cpp OrdersList.h Product.cpp Product.h ProductListPage.cpp ProductListPage.h Provider.cpp Provider.h ProviderStorePage.cpp ProviderStorePage.h RegistrationPage.cpp RegistrationPage.h SelectionCityPage.cpp SelectionCityPage.h SelectionSubcategoryPage.cpp SelectionSubcategoryPage.h SingleOrderClientPage.cpp SingleOrderClientPage.h SingleOrderProviderPage.cpp SingleOrderProviderPage.h Store.cpp Store.h user.cpp User.h UsersDataListPage.cpp UsersDataListPage.h)
add_executable(ingrosso_online main.cpp)
add_library(core STATIC ${SOURCE_FILES})
set_target_properties(core PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libcore.a)
target_link_libraries(ingrosso_online core)
target_link_libraries(ingrosso_online SQLiteCpp sqlite3)
target_include_directories(ingrosso_online PRIVATE SQLiteCpp/include)
target_link_libraries(ingrosso_online ${wxWidgets_LIBRARIES})
