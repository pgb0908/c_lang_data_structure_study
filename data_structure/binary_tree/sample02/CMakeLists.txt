add_executable(binaryTree_sample02 main.cpp)

add_library(BST BinarySearchTree.cpp)

target_link_libraries(binaryTree_sample02 BST)