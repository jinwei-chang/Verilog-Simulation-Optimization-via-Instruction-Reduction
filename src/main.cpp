#include <bits/stdc++.h>
using namespace std;

#define RELEASE
// #define DEBUG

static unordered_set<int> wireOutList;

struct Component{
    Component(
        int type = TYPE::NONE, 
        int ID = 0, 
        int MSB = 0, 
        int LSB = 0,
        Component *left = nullptr,
        Component *right = nullptr,
        Component *parent = nullptr
    ) : 
        _type(type),
        _ID(ID),
        _MSB(MSB),
        _LSB(LSB),
        _left(left),
        _right(right),
        _parent(parent),
        _enable(true)
    {
        
    }

    bool operator==(const Component &right) const{
        if(_type != right._type)
            return false;
        if(_ID != right._ID)
            return false;

        return true;
    }

    string make_inst(){
        Component *cur = this;
        string inst;

        if(cur->_type == TYPE::NOT){
            inst += "~";
            cur = cur->_left;
        }

        if(cur->_type == TYPE::BIT){
            inst += "1'b";
            if(cur->_ID == 0){
                inst += to_string(cur->_ID);
            }
            else{
                inst += to_string(cur->_ID);
            }
        }
        else if(cur->_type == TYPE::IN){
            inst += "in[";
            inst += to_string(cur->_ID);
            inst += "]";
        }
        else if(cur->_type == TYPE::OUT){
            inst += "out[";
            inst += to_string(cur->_ID);
            inst += "]";
        }
        else if(cur->_type == TYPE::WIRE){
            inst += "xformtmp";
            inst += to_string(cur->_ID);
        }
        else if(cur->_type == TYPE::OR){
            inst += cur->_left->make_inst();
            inst += " | ";
            inst += cur->_right->make_inst();
        }
        else if(cur->_type == TYPE::AND){
            inst += cur->_left->make_inst();
            inst += " & ";
            inst += cur->_right->make_inst();
        }
        else if(cur->_type == TYPE::XOR){
            inst += cur->_left->make_inst();
            inst += " ^ ";
            inst += cur->_right->make_inst();
        }

        return inst;
    }

    string make_wire_inst(){
        return "\twire xformtmp" + to_string(_ID) + ";\n";
    }

    string make_assign_inst(){
        return "\tassign " + make_inst() + " = " + _left->make_inst() + ";\n";
    }

    string post_order_make_inst(){
        string inst;

        if(_left != nullptr){
            inst += _left->post_order_make_inst();
        }
        if(_right != nullptr){
            inst += _right->post_order_make_inst();
        }

        if(_type == TYPE::WIRE && !wireOutList.count(_ID)){
            wireOutList.insert(_ID);
            inst += make_wire_inst();
            inst += make_assign_inst();
        }
        else if(_type == TYPE::OUT){
            inst += make_assign_inst();
        }

        return inst;
    }

    Component *_left;
    Component *_right;
    Component *_parent;

    int _type;
    enum TYPE{
        NONE,
        BIT,
        IN,
        OUT,
        WIRE,
        NOT,
        OR,
        AND,
        XOR
    };

    int _MSB;
    int _LSB;
    int _ID;

    bool _enable;
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

// for debug

ostream &operator<<(ostream &out, const Component &right){
    out << "<";
    out << TypeToString[right._type]; 
    out << "> ";
    out << right._ID;
    out << " current: " << &right;
    out << " parent: " << right._parent;
    out << "\n";

    if(right._left != nullptr){
        out << " (Left) " << *right._left;
    }

    if(right._right != nullptr){
        out << " (Right) "<< *right._right;
    }

    return out;
}

static Component bit1(Component::TYPE::BIT, 1, 1, 1, nullptr, nullptr);
static Component bit0(Component::TYPE::BIT, 0, 0, 0, nullptr, nullptr);

static unordered_map<int, Component*> wireList;

static unordered_map<int, Component*> inList;
static map<int, Component*> outList;

void assign(Component *assigned, string leftItem, string rightItem = ""){
    string &item = leftItem;

    if(item == "1'b1" || item == "~1'b0"){
        assigned->_left = &bit1;
    }
    else if(item == "1'b0" || item == "~1'b1"){
        assigned->_left = &bit0;
    }
    else if(item.find("origtmp") == 0){
        assigned->_left = wireList[stoi(item.substr(7))];
        assigned->_left->_parent = assigned;
    }
    else if(item.find("~origtmp") == 0){
        assigned = assigned->_left = new Component(Component::TYPE::NOT, 0, 0, 0, nullptr, nullptr, assigned);
        assigned->_left = wireList[stoi(item.substr(8))];
        assigned->_left->_parent = assigned;
    }
    else if(item.find("in") == 0){
        int idx = stoi(item.substr(item.find('[') + 1, item.find(']') - item.find('[') - 1));
        assigned->_left = inList[idx];
    }
    else if(item.find("~in") == 0){
        assigned = assigned->_left = new Component(Component::TYPE::NOT, 0, 0, 0, nullptr, nullptr, assigned);
        int idx = stoi(item.substr(item.find('[') + 1, item.find(']') - item.find('[') - 1));
        assigned->_left = inList[idx];
    }
    else{
        clog << "<?> " << item << "\n";
    }

    item = rightItem;
    if(item != ""){
        if(item == "1'b1" || item == "~1'b0"){
            assigned->_right = &bit1;
        }
        else if(item == "1'b0" || item == "~1'b1"){
            assigned->_right = &bit0;
        }
        else if(item.find("origtmp") == 0){
            assigned->_right = wireList[stoi(item.substr(7))];
            assigned->_right->_parent = assigned;
        }
        else if(item.find("~origtmp") == 0){
            assigned = assigned->_right = new Component(Component::TYPE::NOT, 0, 0, 0, nullptr, nullptr, assigned);
            assigned->_right = wireList[stoi(item.substr(8))];
            assigned->_right->_parent = assigned;
        }
        else if(item.find("in") == 0){
            int idx = stoi(item.substr(item.find('[') + 1, item.find(']') - item.find('[') - 1));
            assigned->_right = inList[idx];
        }
        else if(item.find("~in") == 0){
            assigned = assigned->_right = new Component(Component::TYPE::NOT, 0, 0, 0, nullptr, nullptr, assigned);
            int idx = stoi(item.substr(item.find('[') + 1, item.find(']') - item.find('[') - 1));
            assigned->_right = inList[idx];
        }
        else{
            clog << "<?> " << item << "\n";
        }
    }
}

void post_order_reduction(Component *cur){
        if(cur->_type == Component::TYPE::BIT || cur->_type == Component::TYPE::IN)
            return;
        
        if(cur->_left != nullptr){
            post_order_reduction(cur->_left);
        }
        if(cur->_right != nullptr){
            post_order_reduction(cur->_right);
        }

        if(cur->_type == Component::TYPE::OUT){

        }
        else if(cur->_type == Component::TYPE::WIRE){
            if(cur->_parent != nullptr){
                if(cur->_left->_type == Component::TYPE::BIT){
                    if(cur->_parent->_left == cur){
                        cur->_parent->_left = cur->_left;
                    }
                    else if(cur->_parent->_right == cur){
                        cur->_parent->_right = cur->_left;
                    }
                }
                else if(cur->_left->_type == Component::TYPE::IN){
                    if(cur->_parent->_left == cur){
                        cur->_parent->_left = cur->_left;
                    }
                    else if(cur->_parent->_right == cur){
                        cur->_parent->_right = cur->_left;
                    }
                }
                else if(cur->_left->_type == Component::TYPE::WIRE){
                    if(cur->_parent->_left == cur){
                        cur->_parent->_left = cur->_left;
                    }
                    else if(cur->_parent->_right == cur){
                        cur->_parent->_right = cur->_left;
                    }
                }
                else if(cur->_left->_type == Component::TYPE::NOT){
                    if(cur->_parent->_left == cur){
                        cur->_parent->_left = cur->_left;
                        cur->_left = cur;
                    }
                    else if(cur->_parent->_right == cur){
                        cur->_parent->_right = cur->_left;
                        cur->_left = cur;
                    }
                }
            }
            
        }
        else if(cur->_type == Component::TYPE::NOT){
            if(cur->_left->_type == Component::TYPE::BIT){
                if(*cur->_left == bit0){
                    cur->_parent->_left = &bit1;
                }
                else if(*cur->_left == bit1){
                    cur->_parent->_left = &bit0;
                }
            }
        }
        else if(cur->_type == Component::TYPE::OR){
            if(*cur->_left == bit1 || *cur->_right == bit1){
                cur->_parent->_left = &bit1;
            }
            else if(*cur->_left == bit0){
                cur->_parent->_left = cur->_right;
            }
            else if(*cur->_right == bit0){
                cur->_parent->_left = cur->_left;
            }
            else if(
                *cur->_left == bit0 && *cur->_right == bit1 ||
                *cur->_left == bit1 && *cur->_right == bit0 ||
                *cur->_left == bit1 && *cur->_right == bit1
                ){
                    cur->_parent->_left = &bit1;
            }
            else if(*cur->_left == bit0 && *cur->_right == bit0){
                cur->_parent->_left = &bit0;
            }
            else if(*cur->_left == *cur->_right){
                cur->_parent->_left = cur->_left;
            }
        }
        else if(cur->_type == Component::TYPE::AND){
            if(*cur->_left == bit0 || *cur->_right == bit0){
                cur->_parent->_left = &bit0;
            }
            else if(*cur->_left == bit1){
                cur->_parent->_left = cur->_right;
            }
            else if(*cur->_right == bit1){
                cur->_parent->_left = cur->_left;
            }
            else if(
                *cur->_left == bit0 && *cur->_right == bit0 ||
                *cur->_left == bit0 && *cur->_right == bit1 ||
                *cur->_left == bit1 && *cur->_right == bit0
                ){
                    cur->_parent->_left = &bit0;
            }
            else if(*cur->_left == bit1 && *cur->_right == bit1){
                cur->_parent->_left = &bit1;
            }
            else if(*cur->_left == *cur->_right){
                cur->_parent->_left = cur->_left;
            }
        }
        else if(cur->_type == Component::TYPE::XOR){
            if(
                *cur->_left == bit0 && *cur->_right == bit1 ||
                *cur->_left == bit1 && *cur->_right == bit0
                ){
                    cur->_parent->_left = &bit1;
            }
            else if(*cur->_left == bit0){
                cur->_parent->_left = cur->_right;
            }
            else if(*cur->_right == bit0){
                cur->_parent->_left = cur->_left;
            }
            else if(*cur->_left == *cur->_right){
                cur->_parent->_left = &bit0;
            }
        }
    }

void parser(ifstream &in, ofstream &out){
    string line;
    bool opt = false;
    while(getline(in, line)){
        // clog << line << endl;

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
            // origtmp#
            int id = stoi(val.substr(7));

            wireList.insert(make_pair( id, new Component(Component::TYPE::WIRE, id, 0, 0, nullptr, nullptr) ));
        }
        else if(kw == "assign"){
            string lhs; ss >> lhs;
            Component *L;
            
            if(lhs.substr(0, 3) == "out"){
                // out[#]
                int idx = stoi(lhs.substr(lhs.find('[') + 1, lhs.find(']') - lhs.find('[') - 1));
                L = outList[idx];
            }
            else{
                // origtmp#
                int idx = stoi(lhs.substr(7));
                L = wireList[idx];
            }
            
            // clog << "assign: " << assign << "\n";

            string eq; ss >> eq;
            string rhs; getline(ss, rhs, ';');
            stringstream split(rhs);
            

            string item1, op, item2;

            split >> item1;
            split >> op;
            split >> item2;

            // clog << item1 << "\n";
            // clog << op << "\n";
            // clog << item2 << "\n";

            if(op == ""){
                // clog << "<log> none op" << endl;
                assign(L, item1);
            }
            else{
                Component *opr;
                if(op == "&"){
                    opr = new Component(Component::TYPE::AND, 0, 0, 0, nullptr, nullptr, L);
                }
                else if(op == "|"){
                    opr = new Component(Component::TYPE::OR, 0, 0, 0, nullptr, nullptr, L);
                }
                else if(op == "^"){
                    opr = new Component(Component::TYPE::XOR, 0, 0, 0, nullptr, nullptr, L);
                }

                assign(opr, item1, item2);

                L->_left = opr;
            }

        }
        else if(kw == "endmodule" && !opt){
            #ifdef DEBUG
            clog << "<Debug> Before" << endl;
            for(auto &it: outList){
                clog << *it.second << "\n";
            }
            #endif
            
            opt = true;

            //* optimize
            //* Post-order Reduction
            for(auto &it: outList){
                post_order_reduction(it.second);
            }

            //* output result
            for(auto &it: outList){
                out << it.second->post_order_make_inst();
            }

            // for(auto &it: wireList){
            //     out << it.second->make_wire_inst();
            // }
            // for(auto &it: outList){
            //     out << it.second->make_assign_inst();
            // }
            // for(auto &it: wireList){
            //     out << it.second->make_assign_inst();
            // }

            #ifdef DEBUG
            clog << "<Debug> After" << endl;
            for(auto &it: outList){
                clog << *it.second << "\n";
            }
            #endif

            out << line << "\n";
        }
        else{
            out << line << "\n";
        }
    }
}

int main(int argc, char **argv){
    #ifdef RELEASE
    #elif DEBUG
    #else
        return EXIT_FAILURE
    #endif

    //* input original file
    ifstream fori(argv[1]);
    //* output optimized file
    ofstream fopt(argv[2]);

    parser(fori, fopt);

    fori.close();
    fopt.close();

    return EXIT_SUCCESS;
}