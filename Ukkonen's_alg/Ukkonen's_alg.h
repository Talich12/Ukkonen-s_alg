#include "SuffixTree.h"
#include <chrono>


SuffixTree::SuffixTree(string& str) : text(str)
{
    text += TERMINATION_SYMBOL;
    BuildSuffixTree();
}

void SuffixTree::BuildSuffixTree()
{
    activeNode = root;
    for (size_t i = 0; i < text.length(); i++)
        ExtendSuffixTree(i);
}

int SuffixTree::EdgeLength(Node* node)
{
    return *(node->end) - (node->start) + 1;
}

void SuffixTree::ExtendSuffixTree(int phase)
{
    // ���������� lastCreatedInternalNode = null ����� ������� ������ ����
    lastCreatedInternalNode = nullptr;

    // ���������� end ��� �������
    // ��������� leafEnd ��������� ������� 1, ����� 3: ����������� �������
    leafEnd++;

    // ������� ��������� �������� �������
    remainingSuffixCount++;

    while (remainingSuffixCount > 0)
    {
        // ���� activeLength ����� 0, ����� ���� ������� ������ �� �����
        if (activeLength == 0)
            activeEdge = phase; // ������ �������� ������� � ������ ���������� ����, �� ������� ����� ���������

        // ���� ������� ������ � ������ ��������� �� activeNode ���
        auto find = activeNode->children.find(text[activeEdge]);

        // �� �����
        if (find == activeNode->children.end())
        {
            // ������� ����� �������� ����, ��������� �� activeNode, ����������� ������� ��������
            activeNode->children.insert(make_pair(text[activeEdge], new Node(root, phase, &leafEnd, phase - remainingSuffixCount + 1, activeNode->suffix_index)));
            // � ���� ����� ������� ����� �����. ��������, ��������� �� ��� ��������� ��������� ��������� ���������� �������
            if (lastCreatedInternalNode != nullptr)
            {
                lastCreatedInternalNode->suffix_link = activeNode;
                lastCreatedInternalNode = nullptr;
            }
        }
        else
        {
            // � ����-���� ���� ���� �� activeNode, ������������ ������� ��������, ������ �� ��� ����������
            Node* next = find->second;
            int edge_length = EdgeLength(next);

            // ����� �� ����(-��)
            if (activeLength >= edge_length)
            {
                activeEdge += edge_length;
                activeLength -= edge_length;
                activeNode = next;
                continue; // ����� ������� �� ����� ����������, ������ �� ������ activeLength < edge_length
            }

            // ������� 3: ���� ������� ������ ���� �� ����,
            // �.�. ������� ��� ���� � ������, �� ������ �������� activeLength
            // ��� �� "������ ������" �� ����
            if (text[next->start + activeLength] == text[phase])
            {
                // ���� lastCreatedInternalNode != null
                // ��� ��������, ��� 2-� ������� ���� ��������� ����� (�������� ����� ��. �������)
                // ��������� ��������� � activeNode
                if (lastCreatedInternalNode != nullptr && activeNode != root)
                    lastCreatedInternalNode->suffix_link = activeNode;
                activeLength++;
                break; // ������ �� ����� while
            }

            // ���� ������, ���� �������� ������� ��� �� ����
            // �������� ����� ���������� ��������
            Node* split = new Node(root, next->start, new int(next->start + activeLength - 1), activeNode->suffix_index);
            // �������� � activeNode ����� ��������
            activeNode->children[text[activeEdge]] = split;
            // � "���������" �������� �������, ��������, ������, ��� �� �� "��������"
            next->start += activeLength;
            // �������� ����� �������� ��������
            split->children.insert(make_pair(text[phase], new Node(root, phase, &leafEnd, phase - remainingSuffixCount + 1, activeNode->suffix_index)));
            // �������� ����������� ��������
            split->children.insert(make_pair(text[next->start], next));
            // � �� ������� ��� ��������� ������ ��� �������� ����� ���������� �������
            if (lastCreatedInternalNode != nullptr)
                lastCreatedInternalNode->suffix_link = split;
            lastCreatedInternalNode = split;
        }

        remainingSuffixCount--;

        // ���� activeNode == root, ����� �������� ������� 2, �� ����. activeLength � ����. activeEdge
        // ���, ����� �������, ������������ ����. ������ � ������, ����� activeNode == root
        if (activeNode == root && activeLength > 0)
        {
            activeLength--;
            activeEdge++;
        }
        else if (activeNode != root) // ���� �� activeNode != root, �� �������� ������ �� ��������� ���������� ������
            activeNode = activeNode->suffix_link;
    }
}

// �������� � ������ ������ (������, �� �������), ������� ��������� � ��������� � ������ node
void CountIndex(Node* node, vector<int>& vec)
{
    if (!node) // ����� ��������: ������ ���������
        return;
    for (auto it : node->children) // ����������� ����� ��� ���� �����������
        CountIndex(it.second, vec);
    if (node->suffix_index != -1) // ��� ����� �� �����, ��������� � ������ ��� ������
        vec.push_back(node->suffix_index);
}

char ch = '?';
int level = 0;
int ind = -1;

void Print_suffix_tree(Node* node) {
    ind++;
    int start = node->start;
    int end = *node->end;
    cout << ch << ' ' << level << ' ' << ind << ' ' << start << ' ' << end << endl;
    for (auto it : node->children) {
        level++;
        ch = it.first;
        Print_suffix_tree(it.second);
        level--;
    }
    ind = -1;
}

bool founded = false;
int Substring_search_in_tree(string str, string substr, Node* node) {
    ++ind;
    bool exist = false;
    if (node->start != -1 || node->start != *node->end) {
        for (int i = node->start + 1; i <= *node->end; i++) {
            if (substr[ind] == str[i]) {
                if (ind == substr.size() - 1) {
                    
                    return i - ind;
                }
                ind++;
            }
            else {
                return -1;
            }
        }
    }
    for (auto it : node->children) {
        ch = it.first;
        if (!founded) {
            if (substr[ind] == ch) {
                if (ind == substr.size() - 1) {
                    founded = true;
                    return it.second->start - ind;
                }
                exist = true;
                Substring_search_in_tree(str, substr, it.second);
            }
        }
    }
    if (!exist) {
        return -1;
    }
    ind = -1;
}

void Substring_search_in_string(string str, string substr) {
    SuffixTree tree = SuffixTree(str);
    Substring_search_in_tree(str, substr, tree.root);
}
