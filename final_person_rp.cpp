#include <iostream>
#include<string>
#include<vector>
#include<string.h>
#include<cctype>
#include<set>

struct Node{
    char letter;
    std::vector<Node*> children ={};
    Node(char input_){
        input_ = tolower(input_);
        letter = input_;};
};


class Trie{
public:
    Trie(){};
    Trie(const std::string& input_);
    Trie(const char* input_);
    Trie(const std::vector<std::string>& input_);
    ~Trie();

    void Insert(const std::string& input_);
    void Insert(const char* input_);
    bool Search(const std::string& input_);
    bool Search(const char* input_);
    void Remove(const std::string& input_);
    void Remove(const char* input_);
    std::set<std::string> Contain(const std::string& input_);
    std::set<std::string> Contain(const char* input_);

    int Count()const{return word_cnt;};

private:
    int word_cnt = 0;
    std::vector<Node*> root = {};

};
Trie::Trie(const std::string& input_){
    this->Insert(input_);
    //std::cout << "here" <<'\n';
}

Trie::Trie(const char* input_){
    this->Insert(input_);
}

Trie::Trie(const std::vector<std::string>& input_){
    for(int i = 0; i < input_.size(); ++i){
        this->Insert(input_[i]);
    }
}

void Trie_delete(Node* current){
    if(current->children.size() !=0){
        for(auto& IT : current->children){
            Trie_delete(IT);
        }
    }
    else{  // base case
        delete current;
    }
}

Trie::~Trie(){
    for(auto& IT : root){
        Trie_delete(IT);
    }
};

void Trie::Insert(const std::string& input_){
    //std::cout << "here" <<'\n';
    char tmp = input_[0];  // very letter word of input word
    tmp = tolower(tmp);  // to lower case

    // empty trie
    if(root.size() == 0){
        Node* tmp_root = new Node(tmp);
        root.push_back(tmp_root);

        Node* cur = root[0];  // create trie branch
        for(size_t i=1; i < input_.size(); i++){
            Node* tmp = new Node(input_[i]);  // create node
            cur->children.push_back(tmp);

            cur = tmp;  // renew cur
        }
        word_cnt++;  // add one word
        std::cout << "Successful input" << input_ << '\n';
        return;
    }

    //root != 0
    Node* cur = nullptr;
    for(size_t i=0; i < root.size(); ++i){
        if(root[i]->letter == tmp){
            cur = root[i];
            break;
        }
    }
    // no match
    if(cur == nullptr){
        cur = new Node(input_[0]);
        root.push_back(cur);

        for(size_t i=1; i < input_.size(); i++){
            Node* tmp = new Node(input_[i]);
            cur->children.push_back(tmp);

            cur = tmp;
        }
        word_cnt++;
        std::cout << "Successful input" << input_ << '\n';
        return;
    }
    // got one match
    for(size_t i=1; i < input_.size();++i){
        bool match = false;
       for(size_t k=0; k < cur->children.size(); ++k){
           char a = tolower(input_[i]);
           if(cur->children[k]->letter == a){
               cur = cur->children[k];
               match = true;
               break;
           }
       }
       // no match children
       if(!match){
           Node* tmp = new Node(input_[i]);
           cur->children.push_back(tmp);

           cur = tmp;
       }

    }
    word_cnt++;
    std::cout << "Successful input " << input_ << '\n';
    return;
}

void Trie::Insert(const char* input_){
    char tmp = input_[0];  // very letter word of input word
    tmp = tolower(tmp);  // to lower case
    // empty trie
    if(root.size() == 0){
        Node* tmp_root = new Node(tmp);
        root.push_back(tmp_root);

        Node* cur = root[0];  // create trie branch
        for(size_t i=1; i < strlen(input_); i++){
            char b = tolower(input_[i]);
            Node* tmp = new Node(b);  // create node
            cur->children.push_back(tmp);

            cur = tmp;  // renew cur
        }
        word_cnt++;  // add one word
        std::cout << "Successful input" << input_ << '\n';
        return;
    }

    // non-empty trie
    Node* cur = nullptr;
    for(size_t i=0; i < root.size(); ++i){
        if(root[i]->letter == tmp){
            cur = root[i];
            break;
        }
    }
    // no match
    if(cur == nullptr){
        char b = tolower(input_[0]);
        cur = new Node(b);
        root.push_back(cur);

        for(size_t i=1; i < strlen(input_); i++){
            char c = tolower(input_[i]);
            Node* tmp = new Node(c);
            cur->children.push_back(tmp);

            cur = tmp;
        }
        word_cnt++;
        return;
    }
    // got one match
    for(size_t i=1; i < strlen(input_);++i){
        bool match = false;
        for(size_t k=0; k < cur->children.size(); ++k){
            char e = tolower(input_[i]);
            if(cur->children[k]->letter == e){
                cur = cur->children[k];
                match = true;
                break;
            }
        }
        // no match children
        if(!match){
            char f = tolower(input_[i]);
            Node* tmp = new Node(f);
            cur->children.push_back(tmp);

            cur = tmp;
            continue;
        }
    }
    word_cnt++;
    return;
}

bool Trie::Search(const std::string& input_){
    if(word_cnt == 0)
        return false;
    else{
        Node* cur = nullptr;
        // find match root
        for(size_t i=0; i < root.size();++i){
            char a = tolower(input_[0]);
            if(root[i]->letter == a){
                cur = root[i];
                break;
            }
        }
        if(cur != nullptr){
            for(size_t j=1; j < input_.size();j++){
                bool Find = false;
                for(size_t k=0; k < cur->children.size();k++){
                    char b = tolower(input_[j]);
                    if(b == cur->children[k]->letter){  // find a match
                        cur = cur->children[k];
                        Find = true;
                        break;
                    }
                }
                if(!Find)  // no match
                    return false;
            }
            // find all match
            if(cur->children.size() != 0){
                for(auto& IT : cur->children){
                    if (IT->letter != ' ')
                        return false;
                }
                return true;
            }
            else
                return true;
        }
        // no match
        else{
            return false;
        }


    }
}

bool Trie::Search(const char* input_){
    if(word_cnt == 0)
        return false;
    else{
        Node* cur = nullptr;
        // find match root
        for(size_t i=0; i < root.size();++i){
            char a = tolower(input_[0]);
            if(root[i]->letter == a){
                cur = root[i];
                break;
            }
        }
        if(cur != nullptr){
            for(size_t j=1; j < strlen(input_);j++){
                bool Find = false;
                for(size_t k=0; k < cur->children.size();k++){
                    char b = tolower(input_[j]);
                    if(b == cur->children[k]->letter){  // find a match
                        cur = cur->children[k];
                        Find = true;
                        break;
                    }
                }
                if(!Find)  // no match
                    return false;
            }
            // find all match
            if(cur->children.size() != 0){
                for(auto& IT : cur->children){
                    if (IT->letter != ' ')
                        return false;
                }
                return true;
            }
            else
                return true;
        }
            // no match
        else{
            return false;
        }


    }
}

void Trie::Remove(const std::string& input_){
    if(word_cnt > 0){
        std::vector<Node*> ToDeleted;  // add those node have to be remove
        Node* cur = nullptr;
        for(size_t i=0; i < root.size();++i){
            char a = tolower(input_[0]);
            if(root[i]->letter == a){
                cur = root[i];
                if(root[i]->children.size() <= 1)
                    ToDeleted.push_back(cur);  // possible deleted root_node
                break;
            }
        }
        // find a match
        if(cur != nullptr){
            for(size_t j=1; j < input_.size(); ++j){
                bool Find = false;
                for(size_t k = 0; k < cur->children.size(); ++k){
                    char b = tolower(input_[j]);
                    if(cur->children[k]->letter == b){
                        // less than one children node -> push delete
                        if(cur->children.size() <= 1){
                            ToDeleted.push_back(cur->children[k]);
                            cur = cur->children[k];  // process
                            Find = true;
                            break;
                        }
                        // more than one children
                        else{
                            Find = true;
                            cur = cur->children[k];  // process
                            break;
                        }

                    }
                }
                if(!Find){
                    std::cout << "No match word for " << input_ << '\n';
                    return;
                }
            }
            if(ToDeleted.size() == input_.size()){
                for(auto& ite : ToDeleted)
                    ite->letter = ' ';
            }
            else{
                ToDeleted[ToDeleted.size()-1]->letter = ' ';
            }
            word_cnt--;
            std::cout << input_ << " has been removed !" << '\n';
            return;
        }
        // no match
        else{
            std::cout << "Cannot find match word for "<< input_ << '\n';
            return;
        }
    }
    else{
        std::cout << "this Trie is empty !" << '\n';
    }
}

std::set<std::string> Trie_travsel(Node* current){  // find the children of this node
    std::string tmp = "";
    std::set<std::string> combination_set = {};  // for children node
    if(current->letter == ' '){  // leaf string
        return combination_set;
    }
    else {

        if (current->children.size() != 0){  // has more children node
            for (size_t k = 0; k < current->children.size(); k++) {
                if (current->children[k]->letter != ' ') {  // not empty node
                    std::set<std::string> Kids = Trie_travsel(current->children[k]);  // recursive

                    if(Kids.size() != 0){  // has real children node
                        for(auto& IT : Kids){
                            combination_set.insert(current->letter + IT);
                        }

                    }
                }
            }
            return combination_set;
        }
        else{
            tmp = tmp+ current->letter;
            combination_set.insert(tmp);
            return combination_set;
        }

    }



}

void Trie::Remove(const char* input_){
    if(word_cnt > 0){
        std::vector<Node*> ToDeleted;  // add those node have to be remove
        Node* cur = nullptr;
        for(size_t i=0; i < root.size();++i){
            char a = tolower(input_[0]);
            if(root[i]->letter == a){
                cur = root[i];
                if(root[i]->children.size() <= 1)
                    ToDeleted.push_back(cur);  // possible deleted root_node
                break;
            }
        }
        // find a match
        if(cur != nullptr){
            for(size_t j=1; j < strlen(input_); ++j){
                bool Find = false;
                for(size_t k = 0; k < cur->children.size(); ++k){
                    char b = tolower(input_[j]);
                    if(cur->children[k]->letter == b){
                        // less than one children node -> push delete
                        if(cur->children.size() <= 1){
                            ToDeleted.push_back(cur->children[k]);
                            cur = cur->children[k];  // process
                            Find = true;
                            break;
                        }
                            // more than one children
                        else{
                            Find = true;
                            cur = cur->children[k];  // process
                            break;
                        }

                    }
                }
                if(!Find){
                    std::cout << "No match word for " << input_ << '\n';
                    return;
                }
            }
            if(ToDeleted.size() == strlen(input_)){
                for(auto& ite : ToDeleted)
                    ite->letter = ' ';
            }
            else{
                ToDeleted[ToDeleted.size()-1]->letter = ' ';
            }
            word_cnt--;
            std::cout << input_ << " has been removed !" << '\n';
            return;
        }
            // no match
        else{
            std::cout << "Cannot find match word for "<< input_ << '\n';
            return;
        }
    }
    else{
        std::cout << "this Trie is empty !" << '\n';
    }
}

std::set<std::string> Trie::Contain(const std::string& input_){
    if(word_cnt > 0){
        std::set<std::string> all_combination;
        std::string connect = input_;
        size_t target_size = input_.size();
        Node* cur = nullptr;
        // find the correct node in root
        for(size_t i=0; i < root.size();++i){
            if(root[i]->letter == tolower(input_[0])){
                cur = root[i];
                // find one
                break;
            }
        }
        // find the root node
        if(cur != nullptr){
            // check
            for(size_t k=1; k < target_size;k++) {
                bool Find = false;
                for (size_t j = 0; j < cur->children.size(); j++) {
                    if (cur->children[j]->letter == input_[k]){
                        cur = cur->children[j];
                        Find = true;
                        break;
                    }
                }
                if(!Find){
                    std::cout << "NO match for " <<  input_ <<'\n';
                    return all_combination;
                }
            }
            // end word
            if(cur == nullptr){
                all_combination.insert(input_);
                return all_combination;
            }
            // have kids
            if(cur->children.size() > 0){
                all_combination = Trie_travsel(cur);
                if(input_.size() > 1) {
                    std::set<std::string> Recommend;
                    std::string sub_input_ = input_.substr(0,input_.size()-1);
                    for (auto &IT : all_combination) {
                        Recommend.insert(sub_input_ + IT);
                    }

                    return Recommend;
                }
                else{
                    return all_combination;
                }

            }
            // no more kids
            else{
                all_combination.insert(input_);
                return all_combination;
            }
        }
        else{
            std::cout << "NO match for " <<  input_ <<'\n';
            return all_combination;
        }
    }
    else{
        std::cout << "Empty Trie. Try to insert some words !";
    }
}

std::set<std::string> Trie::Contain(const char* input_){
    std::string STD_input_ = "";
    for(size_t i = 0; i < strlen(input_); i++){
        STD_input_ += input_[i];
    }

    if(word_cnt > 0){
        std::set<std::string> all_combination;
        size_t target_size = strlen(input_);
        Node* cur = nullptr;
        for(size_t i=0; i < root.size();++i){
            char a = tolower(input_[0]);
            if(root[i]->letter == a){
                cur = root[i];
                // find one
                break;
            }
        }
        if(cur != nullptr){
            // check
            for(size_t k=1; k < target_size;k++) {
                bool Find = false;
                for (size_t j = 0; j < cur->children.size(); j++) {
                    char b = tolower(input_[k]);
                    if (cur->children[j]->letter == b){
                        cur = cur->children[j];
                        Find = true;
                        break;
                    }
                }
                if(!Find){
                    std::cout << "NO match for " <<  input_ <<'\n';
                    return all_combination;
                }
            }
            // input_itself is end word
            if(cur == nullptr){
                all_combination.insert(STD_input_);
                return all_combination;
            }
            if(cur->children.size() > 0){
                all_combination = Trie_travsel(cur);
                if(strlen(input_) > 1) {
                    std::set<std::string> Recommend;
                    std::string sub_input_ = STD_input_.substr(0,strlen(input_)-1);
                    for (auto &IT : all_combination) {
                        Recommend.insert(sub_input_ + IT);
                    }

                    return Recommend;
                }
                else{
                    return all_combination;
                }
            }
                // no more kids
            else{
                all_combination.insert(STD_input_);
                return all_combination;
            }
        }
        else{
            std::cout << "NO match for " <<  input_ <<'\n';
            return all_combination;
        }
    }
    else{
        std::cout << "Empty Trie. Try to insert some words !";
    }
}



int main() {

    Trie Dictionary;
    bool end = false;
    while(!end){
        int command = 0;

        std::cout << "''''''''Welcomne to Trie demo ! ''''''''''" << '\n';
        std::cout << "input command ! ->" <<'\n';
        std::cout << "                  " << '\n';
        std::cout << "Insert : 1" << '\n';
        std::cout << "Search : 2" << '\n';
        std::cout << "Possible word : 3" << '\n';
        std::cout << "Delete : 4" << '\n';
        std::cin >> command;
        switch (command) {
            case 1:{
                std::string a;
                std::cout << "input word to insert: " << '\n';
                std::cin >> a;
                Dictionary.Insert(a);
                break;
            }
            case 2:{
                std::string b;
                std::cout << "input word to Search: " << '\n';
                std::cin >> b;
                std::cout << std::boolalpha << Dictionary.Search(b) << '\n';
                break;
            }
            case 3:{
                std::string c;
                std::cout << "input word to view all possible words: " << '\n';
                std::cin >> c;
                std::set<std::string> possible = Dictionary.Contain(c);
                for(auto& IT : possible){
                    std::cout << IT << '\n';
                }

                break;
            }
            case 4:{
                std::string d;
                std::cout << "input word to delete: " << '\n';
                std::cin >> d;
                Dictionary.Remove(d);
                break;
            }
            case 5:{
                std::cout << "End of Demo" <<'\n';
                end = true;
                break;
            }
            default:{
                std::cout << "No such command " << command << " please try again !" << std::endl;
                break;
            }
        }
    }


    return 0;
}
