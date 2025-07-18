#include <iostream>
#include <vector>
#include <list>     // ���� ����Ʈ (ü�̴� ����)
#include <string>
#include <utility>  // std::pair

// --------------------------------------------------------
// std::unordered_map�� ���� ������ ����� ������ �ؽ� ���̺�
// --------------------------------------------------------
template<typename Key, typename Value>
class MyUnorderedMap {
public:
    // ��Ŷ�� �⺻ ũ��
    static const int DEFAULT_BUCKET_SIZE = 10;

    // �� ��Ŷ�� (Key, Value) ���� �����ϴ� ���� ����Ʈ
    // std::list<std::pair<Key, Value>> : ü�̴��� ���� ���� ����Ʈ
    std::vector<std::list<std::pair<Key, Value>>> buckets;

    MyUnorderedMap() : buckets(DEFAULT_BUCKET_SIZE) {
        std::cout << "MyUnorderedMap�� " << DEFAULT_BUCKET_SIZE << "���� ��Ŷ���� �ʱ�ȭ�Ǿ����ϴ�." << std::endl;
    }

    // ������ �ؽ� �Լ� (���� Ű���� ��ȿ)
    // ���� std::unordered_map�� std::hash�� ����մϴ�.
    size_t getHash(const Key& key) const {
        return std::hash<Key>{}(key); // std::hash ���ø� ��� (�� �Ϲ���)
    }

    // Ű�� ��Ŷ �ε����� ��ȯ
    size_t getBucketIndex(const Key& key) const {
        return getHash(key) % buckets.size();
    }

    // ------------------- ���� ���� -------------------
    void insert(const Key& key, const Value& value) {
        size_t hash_value = getHash(key);
        size_t bucket_idx = getBucketIndex(key);

        std::cout << "\n[���� �õ�: Key=" << key << ", Value=" << value << "]";
        std::cout << " -> �ؽ� ��: " << hash_value << ", ��Ŷ �ε���: " << bucket_idx << std::endl;

        // �ش� ��Ŷ�� ���� ����Ʈ Ž��
        for (auto& pair : buckets[bucket_idx]) {
            if (pair.first == key) {
                std::cout << "  Ű " << key << "�� �̹� �����մϴ�. �� ������Ʈ." << std::endl;
                pair.second = value; // �� ������Ʈ
                return;
            }
        }

        // Ű�� ������ ����Ʈ�� �߰�
        buckets[bucket_idx].push_back({ key, value });
        std::cout << "  ���ο� (Key, Value) �� {" << key << ", " << value << "}�� ��Ŷ " << bucket_idx << "�� �����߽��ϴ�." << std::endl;
        printBucketContent(bucket_idx);
    }

    // ------------------- Ž�� ���� -------------------
    Value* find(const Key& key) {
        size_t hash_value = getHash(key);
        size_t bucket_idx = getBucketIndex(key);

        std::cout << "\n[Ž�� �õ�: Key=" << key << "]";
        std::cout << " -> �ؽ� ��: " << hash_value << ", ���� ��Ŷ �ε���: " << bucket_idx << std::endl;

        // �ش� ��Ŷ�� ���� ����Ʈ Ž��
        std::cout << "  ��Ŷ " << bucket_idx << "�� ������ ��ȸ�ϸ� Ű " << key << "�� ã���ϴ�: ";
        bool first_item = true;
        for (auto& pair : buckets[bucket_idx]) {
            if (!first_item) std::cout << " -> ";
            std::cout << "{" << pair.first << ", " << pair.second << "}";
            first_item = false;

            if (pair.first == key) {
                std::cout << " -> ã�ҽ��ϴ�!" << std::endl;
                return &pair.second; // ���� ������ ��ȯ
            }
        }

        std::cout << " -> ã�� ���߽��ϴ�." << std::endl;
        return nullptr; // ã�� ����
    }

    // ------------------- �����/�ð�ȭ ��ƿ��Ƽ -------------------

    // Ư�� ��Ŷ�� ������ ���
    void printBucketContent(size_t bucket_idx) const {
        if (bucket_idx >= buckets.size()) {
            std::cout << "��ȿ���� ���� ��Ŷ �ε����Դϴ�." << std::endl;
            return;
        }
        std::cout << "  [��Ŷ " << bucket_idx << " ����]: ";
        if (buckets[bucket_idx].empty()) {
            std::cout << "�������";
        }
        else {
            for (const auto& pair : buckets[bucket_idx]) {
                std::cout << "{" << pair.first << ", " << pair.second << "} ";
            }
        }
        std::cout << std::endl;
    }

    // ��ü �ؽ� ���̺��� ���� ���
    void printAllBuckets() const {
        std::cout << "\n===== ���� MyUnorderedMap ���� =====" << std::endl;
        for (size_t i = 0; i < buckets.size(); ++i) {
            std::cout << "��Ŷ " << i << ": ";
            if (buckets[i].empty()) {
                std::cout << "[�������]" << std::endl;
            }
            else {
                for (const auto& pair : buckets[i]) {
                    std::cout << "{" << pair.first << ", " << pair.second << "} -> ";
                }
                std::cout << "nullptr" << std::endl; // ���� ����Ʈ�� ���� �ð������� ǥ��
            }
        }
        std::cout << "=======================================" << std::endl;
    }
};

int main() {
    MyUnorderedMap<int, std::string> myMap;

    // ������ ���� ����
    myMap.insert(10, "Apple");  // �ؽ�: 10, ��Ŷ: 0
    myMap.insert(20, "Banana"); // �ؽ�: 20, ��Ŷ: 0 (�浹!)
    myMap.insert(5, "Cherry");  // �ؽ�: 5, ��Ŷ: 5
    myMap.insert(15, "Date");   // �ؽ�: 15, ��Ŷ: 5 (�浹!)
    myMap.insert(3, "Elderberry"); // �ؽ�: 3, ��Ŷ: 3
    myMap.insert(13, "Fig");    // �ؽ�: 13, ��Ŷ: 3 (�浹!)
    myMap.insert(23, "Grape");  // �ؽ�: 23, ��Ŷ: 3 (�浹!)
    myMap.insert(33, "Honeydew"); // �ؽ�: 33, ��Ŷ: 3 (�浹!)
    myMap.insert(4, "Icecream"); // �ؽ�: 4, ��Ŷ: 4

    myMap.printAllBuckets();

    // ������ Ž�� ����
    std::cout << "\n===== ������ Ž�� =====" << std::endl;

    // �����ϴ� Ű Ž��
    Value* val = myMap.find(20);
    if (val) {
        std::cout << "ã�� ��: " << *val << std::endl;
    }
    else {
        std::cout << "20�� �ش��ϴ� ���� ã�� �� �����ϴ�." << std::endl;
    }

    val = myMap.find(13);
    if (val) {
        std::cout << "ã�� ��: " << *val << std::endl;
    }
    else {
        std::cout << "13�� �ش��ϴ� ���� ã�� �� �����ϴ�." << std::endl;
    }

    // �������� �ʴ� Ű Ž��
    val = myMap.find(99);
    if (val) {
        std::cout << "ã�� ��: " << *val << std::endl;
    }
    else {
        std::cout << "99�� �ش��ϴ� ���� ã�� �� �����ϴ�." << std::endl;
    }

    // �� ������Ʈ �׽�Ʈ
    myMap.insert(10, "New Apple"); // ���� 10�� �� ������Ʈ
    myMap.printBucketContent(0); // 0�� ��Ŷ ���� Ȯ��
    val = myMap.find(10);
    if (val) {
        std::cout << "������Ʈ �� ã�� ��: " << *val << std::endl;
    }

    myMap.printAllBuckets();

    return 0;
}