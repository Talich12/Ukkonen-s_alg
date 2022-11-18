#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

// ���������� ������, ���������� �������� ����������� ���������� true suffix tree
// �.�. ������� ������� �� ����� �������� ��������� ������-���� ������� ��������
#define TERMINATION_SYMBOL '$'

using namespace std;

class SuffixTree;

class Node
{
public:
    friend SuffixTree;

    // ����������� ���� ��� �������: ������������ ��� �������� ����� ���������� ������
    Node(Node* link, int start, int* end, int parent) : Node(link, start, end, -1, parent)
    {
    }

    // ����������� � ��������: ���-�� ��� �������� �������
    // ��� ��� �� �������� ����� ���������� ���������� �� ������
    Node(Node* link, int start, int* end, int ind, int parent) : suffix_link(link),
        start(start),
        end(end),
        suffix_index(ind),
        parent(parent)
    {
    }
    map<char, Node*> children; //������ �����
    int suffix_index; // ����� ��������
    int start;  // ����� ������� ������� ������� � ������
    int* end; // ����� ���������� ������� ������� � ������
    int parent;
private:
    Node* suffix_link;          // ���������� ������
};

class SuffixTree
{
public:
    Node* root = new Node(nullptr, -1, new int(-1), -2); // ������
    SuffixTree(string& text);             // ����������� �� ������
    void BuildSuffixTree();               // ���� ���������� ������
    ~SuffixTree()                         // ����������
    {
        DeleteSuffixTree(root);
    }

private:
    void ExtendSuffixTree(int pos);   // ���������� ������
    void DeleteSuffixTree(Node* node) // �������� ������
    {
        for (auto it : node->children)
            DeleteSuffixTree(it.second);
        if (node->suffix_index == -1)
            delete node->end;
        delete node;
    }
    void CountIndex(Node* node, vector<int>& vec); // ���� �������� ������� � ������, ������������ � ��������� node
    int EdgeLength(Node* node);                    // ������� ����� ��������� ������������� �� ����

    Node* lastCreatedInternalNode = nullptr;         // ��������� ��������� ��������� �������

    string text; // �����, �� �������� �������� ������

    Node* activeNode = nullptr;   // ��, ������ �������� ���������� �� ��������� ����
    int activeEdge = -1;          // ������ �������, ������� ������ �������� �� ������� ����
    int activeLength = 0;         // �� ������� �������� ������� � ����������� activeEdge
    int remainingSuffixCount = 0; // ������� ��������� �������� �������. �� ����, ������� ��������� �� ������� ���� �� �� �������.
    int leafEnd = -1;             // ���������� ����������, ���������� ���������� �������: � ��������� ��� �� ����������� ����� ������ � ���
};