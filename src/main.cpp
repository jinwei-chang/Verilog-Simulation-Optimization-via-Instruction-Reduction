#include <bits/stdc++.h>
using namespace std;

#define DEBUG

struct Component{
    Component(
        int type = TYPE::NONE, 
        int ID = 0, 
        int MSB = 0, 
        int LSB = 0,
        Component *left = nullptr,
        Component *right = nullptr
    ) : 
        _type(type),
        _ID(ID),
        _MSB(MSB),
        _LSB(LSB),
        _left(left),
        _right(right)
    {
        
    }

    Component *_left;
    Component *_right;

    int _type;
    enum TYPE{
        NONE,
        BIT,
        IN,
        OUT,
        WIRE,
        OR,
        AND,
        NOT,
        XOR
    };

    int _MSB;
    int _LSB;
    int _ID;
};

unordered_map<int, const char*> TypeToString = {
    {Component::TYPE::NONE, "NONE"},
    {Component::TYPE::BIT, "BIT"},
    {Component::TYPE::IN, "IN"},
    {Component::TYPE::OUT, "OUT"},
    {Component::TYPE::WIRE, "WIRE"},
    {Component::TYPE::OR, "OR"},
    {Component::TYPE::AND, "AND"},
    {Component::TYPE::NOT, "NOT"},
    {Component::TYPE::XOR, "XOR"},
};

ostream &operator<<(ostream &out, const Component &right){
    out << "<";
    out << TypeToString[right._type]; 
    out << "> ";
    out << right._ID;
    if(right._left != nullptr){
        out << "\n\t" << *right._left;
    }
    if(right._right != nullptr){
        out << "\n\t" << *right._right;
    }

    return out;
}

static Component bit1(Component::TYPE::BIT, 1, 1, 1, nullptr, nullptr);
static Component bit0(Component::TYPE::BIT, 0, 0, 0, nullptr, nullptr);

static unordered_map<int, Component*> wireList;
static unordered_map<int, Component*> inList;
static unordered_map<int, Component*> outList;

void parser(ifstream &in, ofstream &out){
    string line;
    bool opt = false;
    while(getline(in, line)){
        stringstream ss(line);
        string kw;

        ss >> kw;
        if(kw.substr(0, 6) == "output"){
            string val; val = kw.substr(6);
            stringstream split(val);

            int msb, lsb;
            split.ignore();
            split >> msb;
            split.ignore();
            split >> lsb;

            for(int i = lsb; i <= msb; ++i){
                outList.insert(make_pair( i, new Component(Component::TYPE::OUT, i, 0, 0, nullptr, nullptr) ));
            }

            out << line << "\n";
        }
        else if(kw.substr(0, 5) == "input"){
            string val; val = kw.substr(5);
            stringstream split(val);

            int msb, lsb;
            split.ignore();
            split >> msb;
            split.ignore();
            split >> lsb;

            for(int i = lsb; i <= msb; ++i){
                inList.insert(make_pair( i, new Component(Component::TYPE::IN, i, 0, 0, nullptr, nullptr) ));
            }

            out << line << "\n";
        }
        else if(kw == "wire"){
            string val; ss >> val;
            int id = stoi(val.substr(7));

            wireList.insert(make_pair( id, new Component(Component::TYPE::WIRE, id, 0, 0, nullptr, nullptr) ));
        }
        else if(kw == "assign"){
            string lhs; ss >> lhs;
            Component *L;
            int assign;
            if(lhs.substr(0, 3) == "out"){
                assign = stoi(lhs.substr(lhs.find('[') + 1, lhs.find(']') - lhs.find('[') - 1));
                L = outList[assign];
            }
            else{
                assign = stoi(lhs.substr(7));
                L = wireList[assign];
            }
            
            // clog << "assign: " << assign << "\n";

            string eq; ss >> eq;
            string rhs; getline(ss, rhs, ';');
            stringstream split(rhs);
            

            string item1, op, item2;

            split >> item1;
            split >> op;
            split >> item2;

            if(op == ""){
                if(item1.substr(0, 3) == "1'b"){
                    if(item1.substr(3) == "0"){
                        L->_left = &bit0;
                    }
                    else if(item1.substr(3) == "1"){
                        L->_left = &bit1;
                    }
                }
                else if(item1.substr(0, 4) == "~1'b"){
                    if(item1.substr(4) == "0"){
                        L->_left = &bit1;
                    }
                    else if(item1.substr(4) == "1"){
                        L->_left = &bit0;
                    }
                }
                else{
                    clog << "?" << "\n";
                }
            }
            else{
                Component *opr;
                if(op == "&"){
                    opr = new Component(Component::TYPE::AND, 0, 0, 0, nullptr, nullptr);
                }
                else if(op == "|"){
                    opr = new Component(Component::TYPE::OR, 0, 0, 0, nullptr, nullptr);
                }
                else if(op == "^"){
                    opr = new Component(Component::TYPE::XOR, 0, 0, 0, nullptr, nullptr);
                }

                if(item1.substr(0, 3) == "1'b"){
                    if(item1.substr(3) == "0"){
                        opr->_left = &bit0;
                    }
                    else if(item1.substr(3) == "1"){
                        opr->_left = &bit1;
                    }
                }
                else if(item1.substr(0, 4) == "~1'b"){
                    if(item1.substr(4) == "0"){
                        opr->_left = &bit1;
                    }
                    else if(item1.substr(4) == "1"){
                        opr->_left = &bit0;
                    }
                }
                else{
                    clog << "?" << "\n";
                }

                if(item2.substr(0, 3) == "1'b"){
                    if(item2.substr(3) == "0"){
                        opr->_right = &bit0;
                    }
                    else if(item2.substr(3) == "1"){
                        opr->_right = &bit1;
                    }
                }
                else if(item2.substr(0, 4) == "~1'b"){
                    if(item2.substr(4) == "0"){
                        opr->_right = &bit1;
                    }
                    else if(item2.substr(4) == "1"){
                        opr->_right = &bit0;
                    }
                }
                else{
                    clog << "?" << "\n";
                }

                L->_left = opr;
            }

            // clog << item1 << "\n";
            // clog << op << "\n";
            // clog << item2 << "\n";

        }
        else if(kw == "endmodule" && !opt){
            #ifdef DEBUG
            clog << "<debug>" << endl;
            for(auto &it: outList){
                clog << *it.second << "\n";
            }
            #endif
            
            opt = true;
            //* optimize

            //* output result
            

            out << line << "\n";
        }
        else{
            out << line << "\n";
        }
    }
}

int main(int argc, char **argv){
    //* input original file
    ifstream fori(argv[1]);
    //* output optimized file
    ofstream fopt(argv[2]);

    parser(fori, fopt);

    return EXIT_SUCCESS;
}