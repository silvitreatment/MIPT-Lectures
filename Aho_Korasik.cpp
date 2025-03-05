#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// Структура узла Trie
class TrieNode {
public:
    unordered_map<char, TrieNode*> children; // Дочерние узлы (буквы)
    TrieNode* failLink = nullptr; // Fail-ссылка (перейти при несовпадении)
    vector<string> output; // Найденные паттерны (если узел конечный)

    TrieNode() : failLink(nullptr) {}
};

// Основной класс алгоритма Ахо-Корасик
class AhoCorasick {
private:
    TrieNode* root; // Корень Trie

public:
    AhoCorasick() {
        root = new TrieNode();
    }

    // === 1. Добавление слова в Trie ===
    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (!node->children.count(ch)) {
                node->children[ch] = new TrieNode(); // Создаём новую вершину
            }
            node = node->children[ch];
        }
        node->output.push_back(word); // Добавляем слово в выходной список
    }

    // === 2. Построение fail-ссылок (BFS) ===
    void buildFailLinks() {
        queue<TrieNode*> q;
        root->failLink = root; // Корень ссылается сам на себя

        // 1. Инициализируем fail-ссылки для первого уровня Trie
        for (auto& [ch, child] : root->children) {
            child->failLink = root; // Все узлы первого уровня ведут в корень
            q.push(child);
        }

        // 2. BFS: Обрабатываем остальные узлы
        while (!q.empty()) {
            TrieNode* current = q.front();
            q.pop();

            // Перебираем всех детей текущего узла
            for (auto& [ch, child] : current->children) {
                q.push(child); // Добавляем в очередь

                // 3. Поиск fail-ссылки
                TrieNode* fail = current->failLink;
                while (fail != root && !fail->children.count(ch)) {
                    fail = fail->failLink; // Следуем по fail-ссылкам
                }

                // Если нашли, устанавливаем fail-ссылку
                if (fail->children.count(ch)) {
                    child->failLink = fail->children[ch];
                } else {
                    child->failLink = root;
                }

                // 4. Наследуем выходные значения от fail-ссылки
                child->output.insert(child->output.end(),
                                     child->failLink->output.begin(),
                                     child->failLink->output.end());
            }
        }
    }

    // === 3. Поиск паттернов в тексте ===
    vector<pair<int, string>> search(const string& text) {
        vector<pair<int, string>> results; // Результаты (позиция, слово)
        TrieNode* node = root; // Начинаем с корня Trie

        for (int i = 0; i < text.size(); i++) {
            char ch = text[i];

            // Следуем по fail-ссылке, если нет нужного символа
            while (node != root && !node->children.count(ch)) {
                node = node->failLink;
            }

            // Если нашли символ, переходим вперёд
            if (node->children.count(ch)) {
                node = node->children[ch];
            }

            // Если есть найденные слова, записываем их позиции
            for (const string& word : node->output) {
                results.emplace_back(i - word.size() + 1, word);
            }
        }

        return results;
    }
};

// === Тестирование ===
int main() {
    AhoCorasick ac;
    vector<string> patterns = {"he", "she", "his", "hers"};
    string text = "ushers";

    // Добавляем слова в Trie
    for (const string& pattern : patterns) {
        ac.insert(pattern);
    }

    // Строим fail-ссылки
    ac.buildFailLinks();

    // Ищем паттерны в тексте
    vector<pair<int, string>> results = ac.search(text);

    // Вывод результатов
    for (const auto& [index, word] : results) {
        cout << "Паттерн \"" << word << "\" найден на позиции " << index << endl;
    }

    return 0;
}
