#include <bits/stdc++.h>
using namespace std;

void eval_parser(ifstream &in){
    unsigned port = 0;
    unsigned assign_select = 0;

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

            port += msb - lsb + 1;
        }
        else if(kw.substr(0, 5) == "input"){
            string val; val = kw.substr(5);
            stringstream split(val);

            int msb, lsb;
            split.ignore();
            split >> msb;
            split.ignore();
            split >> lsb;

            port += msb - lsb + 1;
        }
        else if(kw == "assign"){
            assign_select += 1.0;

            string lhs; ss >> lhs;
            
            if(lhs.substr(0, 3) == "out"){
                // out[#]
                int idx = stoi(lhs.substr(lhs.find('[') + 1, lhs.find(']') - lhs.find('[') - 1));
                assign_select += 1;
                // cout << lhs << endl;
            }
            
            // clog << "assign: " << assign << "\n";

            string eq; ss >> eq;
            string rhs; getline(ss, rhs, ';');
            stringstream split(rhs);
            

            string item1, op, item2;

            split >> item1;
            split >> op;
            split >> item2;

            if(item1.find("out") == 0 || item1.find("in") == 0 || item1.find("~in") == 0){
                assign_select += 1;
                // cout << item1 << endl;
            }

            if(item2.find("out") == 0 || item2.find("in") == 0 || item2.find("~in") == 0){
                assign_select += 1;
                // cout << item2 << endl;
            }

        }
    }

    cout << "port: " << port << endl;
    cout << "assign_select: " << assign_select << endl;
    cout << "evaluation: " << (double)port / (double)assign_select << endl;
}

int main(int argc, char **argv){
    //* input original file
    ifstream fori(argv[1]);
    //* output optimized file
    ifstream fopt(argv[2]);

    cout << fixed << setprecision(10);

    cout << "<original>" << endl;
    eval_parser(fori);

    cout << "<optimized>" << endl;
    eval_parser(fopt);

    fori.close();
    fopt.close();

    return EXIT_SUCCESS;
}