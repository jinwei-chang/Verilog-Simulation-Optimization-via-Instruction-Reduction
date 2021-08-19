#include <bits/stdc++.h>
using namespace std;

// #define RELEASE
#define DEBUG

static unordered_set<int> wireAssignList;

struct Component{
    Component(
        int type = TYPE::NONE, 
        int ID = 0, 
        int MSB = 0, 
        int LSB = 0,
        Component *left = nullptr,
        Component *right = nullptr,
        Component *parent = nullptr,
        string bitset = "",
        bool sharing = false
    ) : 
        _type(type),
        _ID(ID),
        _MSB(MSB),
        _LSB(LSB),
        _left(left),
        _right(right),
        _parent(parent),
        _bitset(bitset),
        _sharing(sharing),
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

        if(cur->_type == TYPE::BIT){
            inst += to_string(cur->_MSB - cur->_LSB + 1) + "'b";
            inst += cur->_bitset;
        }
        else if(cur->_type == TYPE::IN){
            inst += "in[";
            if(cur->_MSB == cur->_LSB){
                inst += to_string(cur->_MSB);
            }
            else{
                inst += to_string(cur->_MSB) + ":" + to_string(cur->_LSB);
            }
            inst += "]";
        }
        else if(cur->_type == TYPE::OUT){
            inst += "out[";
            if(cur->_MSB == cur->_LSB){
                inst += to_string(cur->_MSB);
            }
            else{
                inst += to_string(cur->_MSB) + ":" + to_string(cur->_LSB);
            }
            inst += "]";
        }
        else if(cur->_type == TYPE::WIRE){
            inst += "xformtmp";
            inst += to_string(cur->_ID);
        }
        else if(cur->_type == TYPE::NOT){
            inst += "~";
            inst += cur->_left->make_inst();
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
        #ifdef DEBUG
        if(_parent != nullptr){
            if(_parent->_left != this && _parent->_right != this){
                clog << "<error> parent error" << endl;
                clog << "<";
                clog << _type; 
                clog << "> ";
                clog << _ID;
                clog << endl;
                clog << " parent: <" << _parent->_type << "> ";
                clog << _parent->_ID;
                clog << endl;
            }
        }

        if(_left != nullptr && _left->_type != TYPE::IN && _left->_type != TYPE::BIT){
            if(_left->_parent != this){
                clog << "<error> left child parent error" << endl;
            }
        }

        if(_right != nullptr && _right->_type != TYPE::IN && _right->_type != TYPE::BIT){
            if(_right->_parent != this){
                clog << "<error> right child parent error" << endl;
            }
        }
        
        #endif

        string inst;

        if(_left != nullptr && _left->_type != TYPE::OUT){
            inst += _left->post_order_make_inst();
        }
        if(_right != nullptr && _right->_type != TYPE::OUT){
            inst += _right->post_order_make_inst();
        }

        if(_type == TYPE::WIRE && !wireAssignList.count(_ID)){
            wireAssignList.insert(_ID);
            #ifdef DEBUG
            inst += make_wire_inst();
            #endif
            inst += make_assign_inst();
        }
        else if(_type == TYPE::OUT && _left != nullptr){
            inst += make_assign_inst();
        }

        return inst;
    }

    string post_order_expression(){
        string expr;

        if(_left != nullptr){
            expr += _left->post_order_expression();
        }
        if(_right != nullptr){
            expr += _right->post_order_expression();
        }

        if(_type == TYPE::IN){
            expr += "I" + to_string(_ID);
        }
        else if(_type == TYPE::NOT){
            expr += "~";
        }
        else if(_type == TYPE::AND){
            expr += "&";
        }
        else if(_type == TYPE::OR){
            expr += "|";
        }
        else if(_type == TYPE::XOR){
            expr += "^";
        }
        else if(_type == TYPE::BIT){
            expr += "B" + _bitset;
        }

        return expr;
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
        XOR,
        ANY,
        BOP
    };

    int _MSB;
    int _LSB;
    int _ID;

    string _bitset;

    bool _sharing;
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

static unordered_map<int, Component*> wireList;
static unordered_map<int, Component*> inList;
static unordered_map<string, Component*> bitsetList;

static map<int, Component*> outList;

bool search_term(Component *head, Component *term, Component::TYPE parent_type, Component *&term_position){
    if(head == nullptr)
        return false;
    
    if(head->_type == parent_type){
        if(head->_left == term || head->_right == term){
            term_position = head;
            return true;
        }
        else if(head->_left->_type != Component::WIRE && head->_right->_type != Component::WIRE){
            return false;
        }
    }
    else if(head->_type == Component::BIT || head->_type == Component::IN){
        return false;
    }
    else if(parent_type == Component::BOP){
        if(head->_type == Component::AND || head->_type == Component::OR || head->_type == Component::XOR){
            if(head->_left == term || head->_right == term){
                term_position = head;
                return true;
            }
        }
        else if(head->_type == Component::NOT){
            return false;
        }
    }
    else if(parent_type == Component::ANY){
        if(head->_left == term || head->_right == term){
            term_position = head;
            return true;
        }
    }

    return search_term(head->_left, term, parent_type, term_position) || search_term(head->_right, term, parent_type, term_position);
}

bool check_same_op(Component *head, Component::TYPE parent_type){
    if(head == nullptr)
        return true;

    if(
        head->_type == Component::AND ||
        head->_type == Component::OR ||
        head->_type == Component::XOR ||
        head->_type == Component::NOT
    ){
        if(head->_type == parent_type){
            return true;
        }
        else{
            return false;
        }
    }

    return check_same_op(head->_left, parent_type) && check_same_op(head->_right, parent_type);
}

void assign_parent(Component *assigned, Component *parent){
    if(
        assigned->_type != Component::BIT &&
        assigned->_type != Component::IN
    ){
        assigned->_parent = parent;
    }
}

void post_order_reduction(Component *cur){
    if(cur->_type == Component::TYPE::BIT || cur->_type == Component::TYPE::IN)
        return;

    // clog << cur->_ID << endl;
    
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
                    assign_parent(cur->_parent->_left, cur->_parent);
                    cur->_enable = false;
                }
                else if(cur->_parent->_right == cur){
                    cur->_parent->_right = cur->_left;
                    assign_parent(cur->_parent->_right, cur->_parent);
                    cur->_enable = false;
                }
            }
            else if(cur->_left->_type == Component::TYPE::IN){
                if(cur->_parent->_left == cur){
                    cur->_parent->_left = cur->_left;
                    assign_parent(cur->_parent->_left, cur->_parent);
                    cur->_enable = false;
                }
                else if(cur->_parent->_right == cur){
                    cur->_parent->_right = cur->_left;
                    assign_parent(cur->_parent->_right, cur->_parent);
                    cur->_enable = false;
                }
            }
            else if(cur->_left->_type == Component::TYPE::WIRE){
                if(cur->_parent->_left == cur){
                    cur->_parent->_left = cur->_left;
                    assign_parent(cur->_parent->_left, cur->_parent);
                    cur->_enable = false;
                }
                else if(cur->_parent->_right == cur){
                    cur->_parent->_right = cur->_left;
                    assign_parent(cur->_parent->_right, cur->_parent);
                    cur->_enable = false;
                }
            }
            // ! do not mix unary and binary
            else if(
                cur->_left->_type == Component::TYPE::NOT &&
                cur->_parent->_type != Component::AND &&
                cur->_parent->_type != Component::OR &&
                cur->_parent->_type != Component::XOR
            ){
                if(cur->_parent->_left == cur){
                    cur->_parent->_left = cur->_left;
                    assign_parent(cur->_parent->_left, cur->_parent);
                    cur->_enable = false;
                    // assign_parent(cur->_parent->_left, cur->_parent);
                    // cur->_left = cur;
                }
                else if(cur->_parent->_right == cur){
                    cur->_parent->_right = cur->_left;
                    assign_parent(cur->_parent->_right, cur->_parent);
                    cur->_enable = false;
                    // assign_parent(cur->_parent->_right, cur->_parent);
                    // cur->_left = cur;
                }
            }
            // else if(cur->_left->_type == Component::TYPE::NOT){
            //     clog << cur->_ID << endl;
            //     clog << cur->_parent->_type << endl;
            // }
        }
    }
    else if(cur->_type == Component::TYPE::NOT){
        if(cur->_left->_type == Component::TYPE::BIT){
            // * not 0 = 1
            if(cur->_left == bitsetList["0"]){
                cur->_parent->_left = bitsetList["1"];
            }
            // * not 1 = 0
            else if(cur->_left == bitsetList["1"]){
                cur->_parent->_left = bitsetList["0"];
            }
        }
        else if(cur->_left->_type == Component::TYPE::WIRE){
            // * not (not A) = A
            if(cur->_left->_left->_type == Component::TYPE::NOT){
                cur->_parent->_left = cur->_left->_left->_left;
                assign_parent(cur->_parent->_left, cur->_parent);
                // if(cur->_left->_left->_left->_type != Component::BIT) cur->_left->_left->_left->_parent = cur->_parent;
            }
        }
        else if(cur->_left->_type == Component::TYPE::NOT){
            cur->_parent->_left = cur->_left->_left;
            assign_parent(cur->_parent->_left, cur->_parent);
        }
    }
    else if(cur->_type == Component::TYPE::OR){
        Component *term_position = nullptr;

        // * 1 or A = 1
        // * A or 1 = 1
        if(cur->_left == bitsetList["1"] || cur->_right == bitsetList["1"]){
            cur->_parent->_left = bitsetList["1"];
        }
        // * 0 or A = A
        if(cur->_left == bitsetList["0"]){
            cur->_parent->_left = cur->_right;
            assign_parent(cur->_parent->_left, cur->_parent);
        }
        // * A or 0 = A
        else if(cur->_right == bitsetList["0"]){
            cur->_parent->_left = cur->_left;
            assign_parent(cur->_parent->_left, cur->_parent);
        }
        // * 0 or 1 = 1
        // * 1 or 0 = 1
        // * 1 or 1 = 1
        // else if(
        //     cur->_left == bitsetList["0"] && cur->_right == bitsetList["1"] ||
        //     cur->_left == bitsetList["1"] && cur->_right == bitsetList["0"] ||
        //     cur->_left == bitsetList["1"] && cur->_right == bitsetList["1"]
        //     ){
        //         cur->_parent->_left = bitsetList["1"];
        // }
        // * 0 or 0 = 0
        // else if(cur->_left == bitsetList["0"] && cur->_right == bitsetList["0"]){
        //     cur->_parent->_left = bitsetList["0"];
        // }
        // * A or A = A
        else if(*cur->_left == *cur->_right){
            cur->_parent->_left = cur->_left;
            assign_parent(cur->_parent->_left, cur->_parent);
        }

        // * A or (A and B) = A
        else if(
            cur->_right->_type == Component::WIRE &&
            cur->_right->_left->_type == Component::AND && (
                cur->_left == cur->_right->_left->_left ||
                cur->_left == cur->_right->_left->_right
            )
            ){
            cur->_parent->_left = cur->_left;
            assign_parent(cur->_parent->_left, cur->_parent);
        }
    }
    else if(cur->_type == Component::TYPE::AND){
        Component *term_position = nullptr;

        // * 0 and A = 0
        // * A and 0 = 0
        if(cur->_left == bitsetList["0"] || cur->_right == bitsetList["0"]){
            cur->_parent->_left = bitsetList["0"];
        }
        // * 1 and A = A
        else if(cur->_left == bitsetList["1"]){
            cur->_parent->_left = cur->_right;
            assign_parent(cur->_parent->_left, cur->_parent);
        }
        // * A and 1 = A
        else if(cur->_right == bitsetList["1"]){
            cur->_parent->_left = cur->_left;
            assign_parent(cur->_parent->_left, cur->_parent);
        }
        // * 0 and 0 = 0
        // * 0 and 1 = 0
        // * 1 and 0 = 0
        // else if(
        //     cur->_left == bitsetList["0"] && cur->_right == bitsetList["0"] ||
        //     cur->_left == bitsetList["0"] && cur->_right == bitsetList["1"] ||
        //     cur->_left == bitsetList["1"] && cur->_right == bitsetList["0"]
        //     ){
        //         cur->_parent->_left = bitsetList["0"];
        // }
        // * 1 and 1 = 1
        // else if(cur->_left == bitsetList["1"] && cur->_right == bitsetList["1"]){
        //     cur->_parent->_left = bitsetList["1"];
        // }
        // * A and A = A
        else if(*cur->_left == *cur->_right){
            cur->_parent->_left = cur->_left;
            assign_parent(cur->_parent->_left, cur->_parent);
        }

        // * (A and B) and A = A and B
        // * (A and B) and B = A and B

        // * (A and B) and (A or *) = A and B
        // * (A and B) and (B or *) = A and B
        else if(
            cur->_left->_type == Component::WIRE &&
            cur->_right->_type == Component::WIRE &&
            cur->_left->_left->_type == Component::AND && (
                search_term(cur->_right, cur->_left->_left->_left, Component::OR, term_position) ||
                search_term(cur->_right, cur->_left->_left->_right, Component::OR, term_position)
            )
        ){
            cur->_parent->_left = cur->_left;
            assign_parent(cur->_parent->_left, cur->_parent);
        }
        // * (A or *) and (A and B) = A and B
        // * (B or *) and (A and B) = A and B
        else if(
            cur->_left->_type == Component::WIRE &&
            cur->_right->_type == Component::WIRE &&
            cur->_right->_left->_type == Component::AND && (
                search_term(cur->_left, cur->_right->_left->_left, Component::OR, term_position) ||
                search_term(cur->_left, cur->_right->_left->_right, Component::OR, term_position)
            )
        ){
            cur->_parent->_left = cur->_right;
            assign_parent(cur->_parent->_left, cur->_parent);
        }
    }
    else if(cur->_type == Component::TYPE::XOR){
        Component *term_position = nullptr;
        // * 0 xor 1 = 1
        // * 1 xor 0 = 1 
        // if(
        //     cur->_left == bitsetList["0"] && cur->_right == bitsetList["1"] ||
        //     cur->_left == bitsetList["1"] && cur->_right == bitsetList["0"]
        //     ){
        //         cur->_parent->_left = bitsetList["1"];
        // }
        // * A xor A = 0
        if(cur->_left == cur->_right){
            cur->_parent->_left = bitsetList["0"];
        }
        // * 0 xor A = A
        else if(cur->_left == bitsetList["0"]){
            cur->_parent->_left = cur->_right;
            assign_parent(cur->_parent->_left, cur->_parent);
        }
        // * A xor 0 = A
        else if(cur->_right == bitsetList["0"]){
            cur->_parent->_left = cur->_left;
            assign_parent(cur->_parent->_left, cur->_parent);
        }
        // * A xor 1 = ~A
        else if(cur->_right == bitsetList["1"]){
            cur->_type = Component::NOT;
            cur->_left = cur->_left;
            cur->_right = nullptr;
            
            // if(cur->_left->_type != Component::BIT) cur->_left->_parent = cur->_parent;
        }
        // * 1 xor A = ~A
        else if(cur->_left == bitsetList["1"]){
            cur->_type = Component::NOT;
            cur->_left = cur->_right;
            cur->_right = nullptr;

            // if(cur->_right->_type != Component::BIT) cur->_right->_parent = cur->_parent;
        }
        // * A xor ~ A = 1
        else if(
            cur->_right->_type == Component::WIRE &&
            cur->_right->_left->_type == Component::NOT &&
            cur->_left == cur->_right->_left->_left
        ){
            cur->_parent->_left = bitsetList["1"];
        }
        // * ~ A xor A = 1
        else if(
            cur->_left->_type == Component::WIRE &&
            cur->_left->_left->_type == Component::NOT &&
            cur->_left->_left->_left == cur->_right
        ){
            cur->_parent->_left = bitsetList["1"];
        }
        
        // * A xor (A + B) = not A and B
        else if(
            cur->_right->_type == Component::WIRE &&
            cur->_right->_left->_type == Component::OR &&
            cur->_left == cur->_right->_left->_left
        ){
            cur->_parent->_left->_type = Component::AND;
            Component *A = cur->_left;
            Component *B = cur->_right->_left->_right;

            cur->_left = B;
            cur->_right->_left->_type = Component::NOT;
            cur->_right->_left->_right = nullptr;
        }
        // * (A xor B xor ... xor *) xor (A xor C xor ... xor *) = B xor ... xor *
        else if(
            check_same_op(cur->_left, Component::XOR) &&
            check_same_op(cur->_right, Component::XOR) &&
            cur->_left->_type == Component::WIRE &&
            cur->_right->_type == Component::WIRE
        ){
            for(unordered_map<int, Component*>::iterator it = inList.begin(); it != inList.end();){
                Component *A = it->second;
                Component *term_position_left = nullptr;
                Component *term_position_right = nullptr;
                if(
                    search_term(cur->_left, A, Component::XOR, term_position_left) && 
                    search_term(cur->_right, A, Component::XOR, term_position_right)
                ){
                    // cout << term_position_left->_parent << endl;
                    // cout << term_position_right->_parent << endl;
                    term_position_left->_parent->_left = A == term_position_left->_right ? term_position_left->_left : term_position_left->_right;
                    assign_parent(term_position_left->_parent->_left, term_position_left->_parent);
                    post_order_reduction(term_position_left->_parent);

                    term_position_right->_parent->_left = A == term_position_right->_right ? term_position_right->_left : term_position_right->_right;
                    assign_parent(term_position_right->_parent->_left, term_position_right->_parent);
                    post_order_reduction(term_position_right->_parent);
                }
                else{
                    ++it;
                }
            }
        }

        // * (A xor B) xor (A xor ... xor *) = B xor ... xor *
        // else if(
        //     cur->_left->_type == Component::WIRE &&
        //     cur->_left->_left->_type == Component::XOR &&
        //     cur->_right->_type == Component::WIRE &&
        //     cur->_right->_left->_type == Component::XOR && (
        //         check_same_op(cur->_right, Component::XOR) &&
        //         search_term(cur->_right, cur->_left->_left->_left, Component::XOR, term_position)
        //     )
        // ){
        //     Component *A = cur->_left->_left->_left;
        //     Component *B = cur->_left->_left->_right;
        //     cur->_left = B;

        //     // clog << term_position << endl;
        //     term_position->_parent->_left = A == term_position->_right ? term_position->_left : term_position->_right;
        //     assign_parent(term_position->_parent->_left, term_position->_parent);
        // }
        // // * (A xor B) xor (B xor ... xor *) = A xor ... xor *
        // else if(
        //     cur->_left->_type == Component::WIRE &&
        //     cur->_left->_left->_type == Component::XOR &&
        //     cur->_right->_type == Component::WIRE &&
        //     cur->_right->_left->_type == Component::XOR && (
        //         check_same_op(cur->_right, Component::XOR) &&
        //         search_term(cur->_right, cur->_left->_left->_right, Component::XOR, term_position)
        //     )
        // ){
        //     Component *A = cur->_left->_left->_left;
        //     Component *B = cur->_left->_left->_right;
        //     cur->_left = A;

        //     // clog << term_position << endl;
        //     term_position->_parent->_left = B == term_position->_right ? term_position->_left : term_position->_right;
        //     assign_parent(term_position->_parent->_left, term_position->_parent);
        // }
        // * (A xor B xor ... xor *) xor (A xor C xor ... xor *) = B xor ... xor *
        // else if(
        //     cur->_left->_type == Component::WIRE &&
        //     cur->_left->_left->_type == Component::XOR && (
        //         check_same_op(cur->_left, Component::XOR)
        //     ) &&
        //     cur->_right->_type == Component::WIRE &&
        //     cur->_right->_left->_type == Component::XOR && (
        //         check_same_op(cur->_right, Component::XOR)
        //     )
        // ){
        //     for(unordered_map<int, Component*>::iterator it = inList.begin(); it != inList.end();){
        //         Component *A = it->second;
        //         Component *term_position_left = nullptr;
        //         Component *term_position_right = nullptr;
        //         if(
        //             search_term(cur->_left, A, Component::XOR, term_position_left) && 
        //             search_term(cur->_right, A, Component::XOR, term_position_right)
        //         ){
        //             // cout << term_position_left->_parent << endl;
        //             // cout << term_position_right->_parent << endl;
        //             term_position_left->_parent->_left = A == term_position_left->_right ? term_position_left->_left : term_position_left->_right;
        //             assign_parent(term_position_left->_parent->_left, term_position_left->_parent);
        //             post_order_reduction(term_position_left->_parent);

        //             term_position_right->_parent->_left = A == term_position_right->_right ? term_position_right->_left : term_position_right->_right;
        //             assign_parent(term_position_right->_parent->_left, term_position_right->_parent);
        //             post_order_reduction(term_position_right->_parent);
        //         }
        //         else{
        //             ++it;
        //         }
        //     }
            
        // }

        

    }
}

// string make_post_order_expression(const Component *head){

//     return "";
// }

unsigned xor_op = 0;
unsigned and_op = 0;
unsigned or_op = 0;
set<Component*> term_set_left;
set<Component*> term_set_right;

bool check_equal(Component *left, Component *right){
    if(left == nullptr && right == nullptr){
        return true;
    }
    else if(left == nullptr || right == nullptr){
        return false;
    }

    if(left->_type != right->_type){
        return false;
    }

    if(
        left->_type == Component::BIT || 
        left->_type == Component::IN ||
        left->_type == Component::OUT
    ){
        if(left != right){
            return false;
        }
    }

    return check_equal(left->_left, right->_left) && check_equal(left->_right, right->_right);
}

bool check_equal_alternative(Component *left, Component *right){
    if(left == nullptr && right == nullptr){
        return true;
    }
    else if(left == nullptr || right == nullptr){
        return false;
    }

    if(left->_type != right->_type){
        return false;
    }

    if(left->_type == Component::BIT){
        if(left != right){
            return false;
        }
    }
    else if(left->_type == Component::IN){
        term_set_left.insert(left);
        term_set_right.insert(right);
    }
    else if(left->_type == Component::XOR){
        ++xor_op;
    }
    else if(left->_type == Component::AND){
        ++and_op;
    }
    else if(left->_type == Component::OR){
        ++or_op;
    }

    return check_equal_alternative(left->_left, right->_left) && check_equal_alternative(left->_right, right->_right);
}

bool combine_equal(Component *left, Component *right){
    if(left == nullptr || right == nullptr){
        return false;
    }
    if(left->_left->_type == Component::BIT && right->_left->_type == Component::BIT){
        return false;
    }

    xor_op = 0;
    and_op = 0;
    or_op = 0;
    term_set_left.clear();
    term_set_right.clear();

    if(check_equal_alternative(left, right)){
        if(xor_op == xor_op + and_op + or_op && term_set_left == term_set_right){
            left->_left = right;
            left->_sharing = true;
        }
        else{
            // clog << (xor_op == xor_op + and_op + or_op) << endl;
            // clog << (term_set_left == term_set_right) << endl;
        }

        return true;
    }
    else if(check_equal(left, right)){
        cout << "combine!" << endl;
        cout << left->_ID << " " << right->_ID << endl;
        left->_left = right;
        left->_sharing = true;
    }
    // cout << left->_ID << " " << right->_ID << endl;

    return false;
}

//* pre-oder traversal
bool check_combinable(Component *left, Component *right){
    if(left == nullptr && right == nullptr){
        return true;
    }
    else if(left == nullptr || right == nullptr){
        return false;
    }

    if(left->_type != right->_type){
        return false;
    }

    if(left->_type == Component::TYPE::BIT){
        return true;
    }

    // clog << "left->_LSB: " << left->_LSB << "\n";
    // clog << "right->_LSB: " << right->_MSB << "\n";
    if(left->_type == Component::TYPE::OUT || left->_type == Component::TYPE::IN){
        if(right->_LSB - left->_MSB != 1){
            return false;
        }
        // return true;
    }

    return check_combinable(left->_left, right->_left) && check_combinable(left->_right, right->_right);
}

void pre_order_combination(Component *left, Component *right, Component *parent = nullptr){
    if(left == nullptr){
        return;
    }
    else if(left->_type == Component::TYPE::OUT){
        left->_MSB = right->_MSB;
    }
    else if(left->_type == Component::TYPE::IN){
        if(left == parent->_left){
            parent->_left = new Component(
                Component::TYPE::IN,
                inList.size(),
                right->_MSB,
                left->_LSB,
                nullptr,
                nullptr,
                nullptr
            );
        }
        else if(left == parent->_right){
            parent->_right = new Component(
                Component::TYPE::IN,
                inList.size(),
                right->_MSB,
                left->_LSB,
                nullptr,
                nullptr,
                nullptr
            );
        }
    }
    else if(left->_type == Component::TYPE::BIT){
        string combine = right->_bitset + left->_bitset;
        if(!bitsetList.count(combine)){
            bitsetList[combine] = new Component(
                    Component::TYPE::BIT,
                    bitsetList.size(),
                    combine.length()-1,
                    0,
                    nullptr,
                    nullptr,
                    nullptr,
                    combine
                );
        }

        parent->_left = bitsetList[combine];
    }

    pre_order_combination(left->_left, right->_left, left);
    pre_order_combination(left->_right, right->_right, left);
}

bool expression_combination(Component *left, Component *right){
    if(check_combinable(left, right)){
        #ifdef DEBUG
        // clog << "yes: " << left->_ID << " " << right->_ID << "\n";
        #endif

        pre_order_combination(left, right);
        outList.erase(right->_ID);
        return true;
    }
    else{
        #ifdef DEBUG
        // clog << "no: " << left->_ID << " " << right->_ID << "\n";
        #endif
    }
        
    return false;
}

void assign(Component *assigned, string leftItem, string rightItem = ""){
    string &item = leftItem;

    if(item == "1'b1" || item == "~1'b0"){
        assigned->_left = bitsetList["1"];
    }
    else if(item == "1'b0" || item == "~1'b1"){
        assigned->_left = bitsetList["0"];
    }
    else if(item.find("origtmp") == 0){
        Component *wire = wireList[stoi(item.substr(7))];
        if(wire->_parent != nullptr){
            int id = wireList.size();
            wire = new Component(Component::TYPE::WIRE, id, 0, 0, wire, nullptr);
            wireList.insert(make_pair( id, wire ));
        }
        assigned->_left = wire;
        assigned->_left->_parent = assigned;
    }
    else if(item.find("~origtmp") == 0){
        assigned = assigned->_left = new Component(Component::TYPE::NOT, 0, 0, 0, nullptr, nullptr, assigned);

        Component *wire = wireList[stoi(item.substr(8))];
        if(wire->_parent != nullptr){
            int id = wireList.size();
            wire = new Component(Component::TYPE::WIRE, id, 0, 0, wire, nullptr);
            wireList.insert(make_pair( id, wire ));
        }
        assigned->_left = wire;
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
            assigned->_right = bitsetList["1"];
        }
        else if(item == "1'b0" || item == "~1'b1"){
            assigned->_right = bitsetList["0"];
        }
        else if(item.find("origtmp") == 0){
            Component *wire = wireList[stoi(item.substr(7))];
            if(wire->_parent != nullptr){
                int id = wireList.size();
                wire = new Component(Component::TYPE::WIRE, id, 0, 0, wire, nullptr);
                wireList.insert(make_pair( id, wire ));
            }
            assigned->_right = wire;
            assigned->_right->_parent = assigned;
        }
        else if(item.find("~origtmp") == 0){
            assigned = assigned->_right = new Component(Component::TYPE::NOT, 0, 0, 0, nullptr, nullptr, assigned);
            
            Component *wire = wireList[stoi(item.substr(8))];
            if(wire->_parent != nullptr){
                int id = wireList.size();
                wire = new Component(Component::TYPE::WIRE, id, 0, 0, wire, nullptr);
                wireList.insert(make_pair( id, wire ));
            }
            assigned->_right = wire;
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

void parser(ifstream &in, ofstream &out){
    out << fixed;
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
                outList.insert(make_pair( i, new Component(Component::TYPE::OUT, i, i, i, nullptr, nullptr) ));
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
                inList.insert(make_pair( i, new Component(Component::TYPE::IN, i, i, i, nullptr, nullptr) ));
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
                //* out[#]
                int idx = stoi(lhs.substr(lhs.find('[') + 1, lhs.find(']') - lhs.find('[') - 1));
                L = outList[idx];
            }
            else{
                //* origtmp#
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

                if(item2.find("in") == 0 || item2.find("~in") == 0){
                    if(item1.find("in") == 0 || item1.find("~in") == 0){
                        int idx1 = stoi(item1.substr(item1.find('[') + 1, item1.find(']') - item1.find('[') - 1));
                        int idx2 = stoi(item2.substr(item2.find('[') + 1, item2.find(']') - item2.find('[') - 1));
                        if(idx2 < idx1){
                            swap(item1, item2);
                        }
                    }
                    else{
                        swap(item1, item2);
                    } 
                }
                // else if(
                //     (item1.find("origtmp") == 0 || item1.find("~origtmp") == 0) &&
                //     (item2.find("origtmp") == 0 || item2.find("~origtmp") == 0) 
                // ){
                //     int idx1 = stoi(item1.substr(7));
                //     int idx2 = stoi(item2.substr(7));
                //     if(idx2 < idx1){
                //         swap(item1, item2);
                //     }
                // }


                assign(opr, item1, item2);

                L->_left = opr;
            }

        }
        else if(kw == "endmodule" && !opt){
            opt = true;

            //* optimize
            //* Post-order Reduction
            for(auto &it: outList){
                post_order_reduction(it.second);
                // post_order_reduction(it.second);
                // post_order_reduction(it.second);
            }
  
            // for(map<int, Component*>::iterator it = outList.begin(); it != prev(outList.end(), 1);){
            //     map<int, Component*>::iterator left = it;
            //     map<int, Component*>::iterator right = next(it, 1);
                
            //     combine_equal(left->second, right->second);
                
            //     ++it;
            // }

            // for(unordered_map<int, Component*>::iterator it = wireList.begin(); it != wireList.end(); ++it){
            //     for(unordered_map<int, Component*>::iterator jt = it; jt != wireList.end(); ++jt){
            //         if(it != jt && it->second->_enable && jt->second->_enable){
            //             combine_equal(it->second, jt->second);
            //         }
            //     }
            // }

            // * equal expression combination
            // * equal post order expression
            unordered_map<string, Component*> hashEquation;
            for(unordered_map<int, Component*>::iterator it = wireList.begin(); it != wireList.end(); ++it){
                if(it->second->_enable){
                    string expr = it->second->post_order_expression();
                    if(!hashEquation.count(expr)){
                        hashEquation[expr] = it->second;
                    }
                    else{
                        // combine_equal(it->second, hashEquation[it->second->post_order_expression()]);
                        // cout << it->second->post_order_expression() << endl;
                        // it->second->_sharing = true;
                        it->second->_left = hashEquation[expr]->_left;
                    }
                }
            }
            for(map<int, Component*>::iterator it = outList.begin(); it != outList.end(); ++it){
                if(it->second->_enable){
                    string expr = it->second->post_order_expression();
                    
                    if(!hashEquation.count(expr)){
                        // cout << expr << endl;
                        hashEquation[expr] = it->second;
                    }
                    else if(expr.find("I") != -1){
                        // combine_equal(it->second, hashEquation[it->second->post_order_expression()]);
                        // cout << it->second->post_order_expression() << endl;
                        // it->second->_sharing = true;
                        if(hashEquation[expr]->_left->_type == Component::IN){
                            it->second->_left = hashEquation[expr];
                        }
                        else if(hashEquation[expr]->_left->_type == Component::NOT && hashEquation[expr]->_left->_left->_type == Component::IN){
                            it->second->_left = hashEquation[expr];
                        }
                        else if(
                            (
                                hashEquation[expr]->_left->_type == Component::AND ||
                                hashEquation[expr]->_left->_type == Component::OR ||
                                hashEquation[expr]->_left->_type == Component::XOR
                            ) &&
                            (
                                hashEquation[expr]->_left->_left->_type == Component::IN &&
                                hashEquation[expr]->_left->_right->_type == Component::IN
                            )
                        ){
                            it->second->_left = hashEquation[expr];
                        }
                        else{
                            it->second->_left = hashEquation[expr]->_left;
                        }
                    }
                }
            }
            
            //* continuous expression combination
            for(map<int, Component*>::iterator it = outList.begin(); it != prev(outList.end(), 1);){
                map<int, Component*>::iterator left = it;
                map<int, Component*>::iterator right = next(it, 1);
                
                if(!expression_combination(left->second, right->second)){
                    ++it;
                }
            }

            //* output result
            #ifdef DEBUG
            for(auto &it: outList){
                out << it.second->post_order_make_inst();
            }
            #endif

            #ifdef RELEASE
            for(auto &it: wireList){
                if(it.second->_enable)
                    out << it.second->make_wire_inst();
            }
            for(auto &it: outList){
                out << it.second->post_order_make_inst();
            }
            #endif
            // for(auto &it: outList){
            //     out << it.second->make_assign_inst();
            // }
            // for(auto &it: wireList){
            //     out << it.second->make_assign_inst();
            // }
            out << line << "\n";
        }
        else{
            out << line << "\n";
        }
    }
}

int main(int argc, char **argv){
    #ifdef RELEASE
    #elif defined DEBUG
    #else
        return EXIT_FAILURE;
    #endif

    //* input original file
    ifstream fori(argv[1]);
    //* output optimized file
    ofstream fopt(argv[2]);

    bitsetList["0"] = new Component(Component::TYPE::BIT, 0, 0, 0, nullptr, nullptr, nullptr, "0");
    bitsetList["1"] = new Component(Component::TYPE::BIT, 1, 0, 0, nullptr, nullptr, nullptr, "1");

    parser(fori, fopt);

    fori.close();
    fopt.close();

    return EXIT_SUCCESS;
}