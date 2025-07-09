#include <unordered_map>


// ========================================
// 2. unordered_map ���� �Լ���
// ========================================

unordered_map<char, int> lastIndex;
lastIndex['a'] = 1;
lastIndex['b'] = 5;
lastIndex['c'] = 10;

// ----------------------------------------
// 2-1. .find() �Լ�
// ----------------------------------------

auto it = lastIndex.find('a');  // iterator ��ȯ
if (it != lastIndex.end()) 
{
    cout << "Ű 'a' ã��: " << it->second << endl;
}

auto it2 = lastIndex.find('z');  // ���� Ű
if (it2 == lastIndex.end()) 
{
    cout << "Ű 'z' ����" << endl;
}

// ----------------------------------------
// 2-2. .end() �Լ�
// ----------------------------------------

.end()�� ���� ���� ��Ÿ���� Ư���� iterator
"ã�� �� ����"�� ��Ÿ���� ��
 
// ----------------------------------------
// 2-3. .count() �Լ�
// ----------------------------------------

// unordered_map������ Ű�� ������ 1, ������ 0 ��ȯ
cout << "Ű 'a' ����: " << lastIndex.count('a') << endl;  // 1
cout << "Ű 'z' ����: " << lastIndex.count('z') << endl;  // 0

// ���� Ȯ�ο����� ���� ���
if (lastIndex.count('a') > 0) 
{
    cout << "Ű 'a' ������" << endl;
}

// ----------------------------------------
// 2-4. .contains() �Լ� (C++20 �̻�)
// ----------------------------------------

// ���� �������� ��� (C++20 �̻󿡼��� ��� ����)
if (lastIndex.contains('a')) 
{
    cout << "Ű 'a' ������ (contains ���)" << endl;
}

if (!lastIndex.contains('z')) 
{
    cout << "Ű 'z' ���� (contains ���)" << endl;
}


// ========================================
// 3. ���� ��� ���� ��
// ========================================

cout << "=== Ű ���� Ȯ�� ��� �� ===" << endl;

char searchKey = 'a';

// ��� 1: find() ���
if (lastIndex.find(searchKey) != lastIndex.end()) {
    cout << "��� 1 (find): Ű ����" << endl;
}

// ��� 2: count() ���
if (lastIndex.count(searchKey) > 0) 
{
    cout << "��� 2 (count): Ű ����" << endl;
}

// ��� 3: contains() ��� (C++20+)
if (lastIndex.contains(searchKey)) 
{
    cout << "��� 3 (contains): Ű ����" << endl;
}


// ========================================
// 4. ���ǻ���
// ========================================


// �߸��� ���: Ű�� ��� �ڵ� ������
cout << "map ũ�� (before): " << lastIndex.size() << endl;
int value = lastIndex['z'];  // 'z' Ű�� �ڵ� ������ (�⺻�� 0)
cout << "map ũ�� (after): " << lastIndex.size() << endl;
cout << "�ڵ� ������ ��: " << value << endl;
