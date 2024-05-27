#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

// ��������� �������� ����������
struct product {
    int article;
    std::string name;
    int quantity;
    std::string tip;
    double sellid;
};

// ����� ��� ���������� ����� ������

class productDB {
private:
    std::vector<product> products;  // ������ �������
    const std::string filename = "wb_db.txt";  // �������� �����

public:
    // �����������
    productDB() {
        loadFromFile();
    }

    // ����������
    ~productDB() {
        saveToFile();
    }

    // �������� ������ �� �����
    void loadFromFile() {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return;
        }

        std::string line;
        while (getline(file, line)) {
            std::stringstream ss(line);
            product product;
            ss >> product.article >> product.name >> product.quantity >> product.tip >> product.sellid;
            products.push_back(product);
        }

        file.close();
    }

    // ���������� ������ � ����
    void saveToFile() {
        std::ofstream file(filename);
        for (const auto& product : products) {
            file << product.article << " " << product.name << " " << product.quantity << " "
                << product.tip << " " << product.sellid << "\n";
        }

        file.close();
    }

    // ����� ��� ���������� ��������
    void addproduct(const product& product) {
        products.push_back(product);
    }

    // �������������� ������ �������� �� ��� �������
    void editproduct(int article, const product& updatedproduct) {
        for (auto& product : products) {
            if (product.article == article) {
                product = updatedproduct;
                break;
            }
        }
    }

    // �������� �������� �� ��� �������
    void deleteproduct(int article) {
        products.erase(std::remove_if(products.begin(), products.end(),
            [article](const product& product) { return product.article == article; }),
            products.end());
    }

    // ����� � ����������� ������ ������ �� ��� �������
    void searchproduct(int article) {
        for (const auto& product : products) {
            if (product.article == article) {
                std::cout << "article: " << product.article << ", Name: " << product.name << ", quantity: " << product.quantity
                    << ", tip: " << product.tip << ", sellid: " << product.sellid << "\n";
                return;
            }
        }

        std::cout << "product not found.\n";
    }

    // ����������� ���� �������
    void listproducts() {
        for (const auto& product : products) {
            std::cout << "article: " << product.article << ", Name: " << product.name << ", quantity: " << product.quantity
                << ", tip: " << product.tip << ", sellid: " << product.sellid << "\n";
        }
    }
};



                  // ����� �������� �������
int main() {
    productDB db;
    int choice;

    do {
        std::cout << "\nDatabase of wildberries articles\n";
        std::cout << "1. Add product\n";
        std::cout << "2. Edit product\n";
        std::cout << "3. Delete product\n";
        std::cout << "4. Search product\n";
        std::cout << "5. List of all products\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter what you want: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            product product;
            std::cout << "Enter article of product: ";
            std::cin >> product.article;
            std::cout << "Enter name of product: ";
            std::cin >> product.name;
            std::cout << "Enter amount: ";
            std::cin >> product.quantity;
            std::cout << "Enter type: ";
            std::cin >> product.tip;
            std::cout << "Enter seller's id: ";
            std::cin >> product.sellid;
            db.addproduct(product);
            break;
        }
        case 2: {
            int article;
            product product;
            std::cout << "Enter article of product to edit: ";
            std::cin >> article;
            std::cout << "Enter new product name: ";
            std::cin >> product.name;
            std::cout << "Enter new product quantity: ";
            std::cin >> product.quantity;
            std::cout << "Enter new type: ";
            std::cin >> product.tip;
            std::cout << "Enter new seller's id: ";
            std::cin >> product.sellid;
            product.article = article;
            db.editproduct(article, product);
            break;
        }
        case 3: {
            int article;
            std::cout << "Enter article of product to delete: ";
            std::cin >> article;
            db.deleteproduct(article);
            break;
        }
        case 4: {
            int article;
            std::cout << "Enter article of product to search: ";
            std::cin >> article;
            db.searchproduct(article);
            break;
        }
        case 5: {
            db.listproducts();
            break;
        }
        case 6: {
            std::cout << "Exiting...\n";
            break;
        }
        default: {
            std::cout << "Invalid.\n";
            break;
        }
        }
    } while (choice != 6);

    return 0;
}
