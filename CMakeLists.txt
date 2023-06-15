cmake_minimum_required(VERSION 3.21)
project(ingrosso_online)

set(CMAKE_CXX_STANDARD 11)

enable_testing()
add_subdirectory(test)
add_subdirectory(SQLiteCpp)

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /CLionProjects/ingrosso/SQLiteCpp)
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} /CLionProjects/ingrosso/SQLiteCpp/include)
find_package(SQLite3 REQUIRED net gl core base media)
include_directories(${SQLite3_INCLUDE_DIRS})
include_directories(SQLiteCpp/include)
find_package(wxWidgets REQUIRED net gl core base media)
include(${wxWidgets_USE_FILE})


set(SOURCE_FILES user.h cart.h favourite.h subcategories.h user.cpp cart.cpp favourite.cpp subcategories.cpp categories.h categories.cpp orderProduct.cpp orderProduct.h store.cpp store.h HomePageClient.cpp HomePageClient.h SelectionSubcategoryPage.cpp SelectionSubcategoryPage.h MyApp.cpp MyApp.h InsertProductPage.cpp InsertProductPage.h HomePageProviders.cpp HomePageProviders.h RegistrationPage.cpp RegistrationPage.h InitialPage.cpp InitialPage.h database.h database.cpp ProductListPage.cpp ProductListPage.h GlobalVariables.cpp GlobalVariables.h ManageProfilePage.cpp ManageProfilePage.h FavouritesListPage.cpp FavouritesListPage.h CartPage.cpp CartPage.h CartPage.h ManageRequestPage.cpp ManageRequestPage.h ManageRequestPage.h SingleOrderDataForProvider.cpp SingleOrderDataForProvider.h SingleOrderDataForProvider.h ProviderStorePage.cpp ProviderStorePage.h ModifyProductPage.cpp ModifyProductPage.h ModifyProductPage.h OrderHistoryForClientPage.cpp OrderHistoryForClientPage.h SingleOrderDataForClient.cpp SingleOrderDataForClient.h SingleOrderDataForClient.h ChooseStatusPage.cpp ChooseStatusPage.h ForgotPasswordPage.cpp ForgotPasswordPage.h UsersDataListPage.cpp UsersDataListPage.h SelectionCityPage.cpp SelectionCityPage.h city.cpp city.h LogInPage.h LogInPage.cpp dbCartManager.cpp dbCartManager.h dbCartManager.h dbFavouritesManager.cpp dbFavouritesManager.h dbFavouritesManager.h)

add_executable(ingrosso_online main.cpp)
add_library(core STATIC ${SOURCE_FILES})
set_target_properties(core PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libcore.a)
target_link_libraries(ingrosso_online core)
target_link_libraries(ingrosso_online SQLiteCpp sqlite3)
target_include_directories(ingrosso_online PRIVATE SQLiteCpp/include)
target_link_libraries(ingrosso_online ${wxWidgets_LIBRARIES})
