cmake_minimum_required(VERSION 3.21)
project(ingrosso_online)

set(CMAKE_CXX_STANDARD 11)

enable_testing()
add_subdirectory(test)
add_subdirectory(SQLiteCpp)

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /CLionProjects/ingrosso/SQLiteCpp)
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} /CLionProjects/ingrosso/SQLiteCpp/include)

include_directories(SQLiteCpp/sqlite3)
include_directories(SQLiteCpp/include)
find_package(wxWidgets REQUIRED net gl core base media)
include(${wxWidgets_USE_FILE})


set(SOURCE_FILES user.h cart.h favourites.h dbSubcategoriesManager.h user.cpp cart.cpp favourites.cpp dbSubcategoriesManager.cpp categories.h categories.cpp orders.cpp orders.h store.cpp store.h HomePageClient.cpp HomePageClient.h SelectionSubcategoryPage.cpp SelectionSubcategoryPage.h MyApp.cpp MyApp.h InsertProductPage.cpp InsertProductPage.h HomePageProviders.cpp HomePageProviders.h RegistrationPage.cpp RegistrationPage.h InitialPage.cpp InitialPage.h database.h database.cpp ProductListPage.cpp ProductListPage.h GlobalVariables.cpp GlobalVariables.h ManageProfilePage.cpp ManageProfilePage.h FavouritesListPage.cpp FavouritesListPage.h CartPage.cpp CartPage.h CartPage.h ManageRequestPage.cpp ManageRequestPage.h ManageRequestPage.h SingleOrderProviderPage.cpp SingleOrderProviderPage.h SingleOrderProviderPage.h ProviderStorePage.cpp ProviderStorePage.h ModifyProductPage.cpp ModifyProductPage.h ModifyProductPage.h OrderHistoryForClientPage.cpp OrderHistoryForClientPage.h SingleOrderClientPage.cpp SingleOrderClientPage.h SingleOrderClientPage.h ChooseStatusPage.cpp ChooseStatusPage.h ForgotPasswordPage.cpp ForgotPasswordPage.h UsersDataListPage.cpp UsersDataListPage.h SelectionCityPage.cpp SelectionCityPage.h dbCityManager.cpp dbCityManager.h LogInPage.h LogInPage.cpp dbCartManager.cpp dbCartManager.h dbCartManager.h dbFavouritesManager.cpp dbFavouritesManager.h dbFavouritesManager.h dbOrdersManager.cpp dbOrdersManager.h dbStoreManager.cpp dbStoreManager.h dbUserManager.cpp dbUserManager.h provider.cpp provider.h client.cpp client.h)

add_executable(ingrosso_online main.cpp)
add_library(core STATIC ${SOURCE_FILES})
set_target_properties(core PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libcore.a)
target_link_libraries(ingrosso_online core)
target_link_libraries(ingrosso_online SQLiteCpp sqlite3)
target_include_directories(ingrosso_online PRIVATE SQLiteCpp/include)
target_link_libraries(ingrosso_online ${wxWidgets_LIBRARIES})
