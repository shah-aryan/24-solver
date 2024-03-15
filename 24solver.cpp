#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class solver
{
  private:
    double a, b, c, d;
    vector<double> nums;
    int result;
    int n;

    //vector<vector<char> > solutions;
    
    struct Solution
    {
        double a, b, c, d;
        char op1, op2, op3;
        int type;

            Solution(double a, double b, double c, double d, char op1, char op2, char op3, int type)
                : a(a), b(b), c(c), d(d), op1(op1), op2(op2), op3(op3), type(type) {}
    };


    vector <Solution> solutions;

  public:
    solver(int pa, int pb, int pc, int pd, int n) :
        a(static_cast<double>(pa)),
        b(static_cast<double>(pb)),
        c(static_cast<double>(pc)),
        d(static_cast<double>(pd)),
        n(n)
    {
        nums.push_back(a);
        nums.push_back(b);
        nums.push_back(c);
        nums.push_back(d);
    }


    double opToFunc(char op, double a, double b)
    {
        switch (op)
        {
        case '+':
            return a + b;
            break;
        case '-':
            return a - b;
            break;
        case '*':
            return a * b;
            break;
        case '/':
            return a / b;
            break;
        }
    }
    
    void solve()
    {
        vector<double> toCheck;
        toCheck.resize(4);
        for (int i = 0; i < 4; i++)
        {
            toCheck[0] = nums[i];
            for (int j = 0; j < 4; j++)
            {
                if (j == i) continue;
                toCheck[1] = nums[j];
                for (int k = 0; k < 4; k++)
                {
                    if (k == j || k == i) continue;
                    toCheck[2] = nums[k];
                    for (int l = 0; l < 4; l++)
                    {
                        if (l == k || l == j || l == i) continue;
                        toCheck[3] = nums[l];

                        doOps(toCheck);
                    }
                }
            }
        }
    }

    void doOps(const vector<double> &nums)
    {
        vector<char> ops;
        ops.push_back('+');
        ops.push_back('-');
        ops.push_back('*');
        ops.push_back('/');
        char op1, op2, op3;

        int result = 0;

        for (int i = 0; i < 4; i++)
        {
            op1 = ops[i];
            for (int j = 0; j < 4; j++)
            {
                op2 = ops[j];
                for (int k = 0; k < 4; k++)
                {
                    op3 = ops[k];

                    computeAndCheck(op1, op2, op3, nums);
                }
            }
        }
    }

    void computeAndCheck(const char op1, const char op2, const char op3, const vector<double> &nums)
    {
        double result = 0;
        
        result = opToFunc(op1, nums[0], nums[1]);
        result = opToFunc(op2, result, nums[2]);
        result = opToFunc(op3, result, nums[3]);
        if (result == 24) solutions.emplace_back(nums[0], nums[1], nums[2], nums[3], op1, op2, op3, 0);
        result = 0;

        result = opToFunc(op2, nums[1], nums[2]);
        result = opToFunc(op1, nums[0], result);
        result = opToFunc(op3, result, nums[3]);
        if (result == 24) solutions.emplace_back(nums[0], nums[1], nums[2], nums[3], op1, op2, op3, 1);
        result = 0;

        result = opToFunc(op2, nums[1], nums[2]);
        result = opToFunc(op3, result, nums[3]);
        result = opToFunc(op1, nums[0], result);
        if (result == 24) solutions.emplace_back(nums[0], nums[1], nums[2], nums[3], op1, op2, op3, 2);
        result = 0;

        result = opToFunc(op3, nums[2], nums[3]);
        result = opToFunc(op2, nums[1], result);
        result = opToFunc(op1, nums[0], result);
        if (result == 24) solutions.emplace_back(nums[0], nums[1], nums[2], nums[3], op1, op2, op3, 3);
        result = 0;

        result         = opToFunc(op1, nums[0], nums[1]);
        double result2 = opToFunc(op3, nums[2], nums[3]);
        result         = opToFunc(op2, result, result2);
        if (result == 24) solutions.emplace_back(nums[0], nums[1], nums[2], nums[3], op1, op2, op3, 4);
        result = 0;

    }

    void printSolution()
    {
        if (solutions.size() == 0)
        {
            std::cout << "No solutions exist to this problem\n";
            return;
        }
        std::cout << solutions.size() << " solutions found\n";
        if (n == -1) n = solutions.size();
        std::cout << "Showing " << n << " solutions\n";

        /*
        types of solutions:
        0: ((a op1 b) op2 c) op3 d
        1: (a op1 (b op2 c)) op3 d
        2: a op1 ((b op2 c) op3 d)
        3: a op1 (b op2 (c op3 d))
        4: (a op1 b) op2 (c op3 d)
        */
       int i = 1;
        for (auto sol : solutions)
        {   
            if (i > n) break;
            std::cout << i++ << ": ";
            switch (sol.type)
            {
                case 0:
                    std::cout << "((" << sol.a << " " << sol.op1 << " " << sol.b << ") " << sol.op2 << " " 
                              << sol.c << ") " << sol.op3 << " " << sol.d << "\n";
                    break;
                case 1:
                    std::cout << "(" << sol.a << " " << sol.op1 << " (" << sol.b << " " << sol.op2 << " " 
                              << sol.c << ")) " << sol.op3 << " " << sol.d << "\n";
                    break;
                case 2:
                    std::cout << sol.a << " " << sol.op1 << " ((" << sol.b << " " << sol.op2 << " " 
                              << sol.c << ") " << sol.op3 << " " << sol.d << ")\n";
                    break;
                case 3:
                    std::cout << sol.a << " " << sol.op1 << " (" << sol.b << " " << sol.op2 << " (" 
                              << sol.c << " " << sol.op3 << " " << sol.d << "))\n";
                    break;
                case 4:
                    std::cout << "((" << sol.a << " " << sol.op1 << " " << sol.b << ") " << sol.op2 << " (" 
                              << sol.c << " " << sol.op3 << " " << sol.d << "))\n";
                    break;
                default:
                    std::cout << "Error\n";
                    break;
            }
        }
    }
};

int main()
{   
    bool p = true;

    std::cout << "Welcome to 24solver\n";
    std::cout << "This program will solve for 24 using 4 numbers and the 4 basic operations\n";
    int a, b, c, d, n;

    while (p)
    {   
        std::cout << "Enter 4 numbers: ";
        std::cout << "\nNumber 1: ";
        cin >> a;
        std::cout << "Number 2: ";
        cin >> b;
        std::cout << "Number 3: ";
        cin >> c;
        std::cout << "Number 4: ";
        cin >> d;
        std::cout << "How many solutions do you want to see? \n" 
            << "Enter -1 to see all solutions: ";
        cin >> n;

        std::cout << "\nSolving for " << a << " " << b << " " << c << " " << d << " and showing " << n << " solutions \n";

        solver s(a, b, c, d, n);
        s.solve();
        s.printSolution();

        std::cout << "\nWould you like to solve another problem? (y/n): ";
        char ans;
        cin >> ans;
        if (ans == 'n') p = false;
        std::cout << "\n";
    }



    std::cout << "Thank you for using 24solver\n";
    std::cout << "Have a great day!\n";

    return 0;
}



/*


        // for (char &c : sol)
        // {
        //     switch (c)
        //     {
        //         case 'a':
        //             doubleDigit(c, nums[0], sol);
        //             break;
        //         case 'b':
        //             doubleDigit(c, nums[1], sol);
        //             break;
        //         case 'c':
        //             doubleDigit(c, nums[2], sol);
        //             break;
        //         case 'd':
        //             doubleDigit(c, nums[3], sol);
        //             break;
        //         default:
        //             break;
        //     }
        // }

                for (auto sol : solutions)
        {

            switch (sol.type)
                {
                case 0:


                    std::cout << "((" << sol.a << " " << sol.op1 << " " << sol.b << ") " << sol.op2 << " " 
                              << sol.c << ") " << sol.op3 << " " << sol.d << "\n";
                    break;
                case 1:
                    // sol[0] = '(';
                    // sol[4] = '(';
                    // sol[10] = ')';
                    // sol.insert(sol.begin()+10, ')');

                    std::cout << "(" << sol.a << " " << sol.op1 << " (" << sol.b << " " << sol.op2 << " " 
                              << sol.c << ")) " << sol.op3 << " " << sol.d << "\n";
                    break;
                case 2:
                    // sol[4] = '(';
                    // sol[10] = ')';
                    // sol[14] = ')';
                    // sol.insert(sol.begin()+4, '(');

                    std::cout << sol.a << " " << sol.op1 << " ((" << sol.b << " " << sol.op2 << " " 
                              << sol.c << ") " << sol.op3 << " " << sol.d << ")\n";
                    break;
                case 3:
                    // sol[4] = '(';
                    // sol[8] = '(';
                    // sol[14] = ')';
                    // sol.insert(sol.begin()+14, ')');

                    std::cout << sol.a << " " << sol.op1 << " (" << sol.b << " " << sol.op2 << " (" 
                              << sol.c << " " << sol.op3 << " " << sol.d << "))\n";
                    break;
                case 4:
                    // sol[0] = '(';
                    // sol[6] = ')';
                    // sol[8] = '(';
                    // sol[14] = ')';

                    std::cout << "((" << sol.a << " " << sol.op1 << " " << sol.b << ") " << sol.op2 << " (" 
                              << sol.c << " " << sol.op3 << " " << sol.d << "))\n";
                    break;
                default:
                    std::cout << "Error\n";
                    break;
                }
                std::cout << "\n";
        
    }


    // void doubleDigit(char& c, double num, vector<char>& sol) {
    //     if (num < 10) {
    //         c = static_cast<char>(num + '0');
    //     }
    //     else {
    //         int num = static_cast<int>(nums[num]);
    //         int index = -1;
    //         for (int i = 0; i < sol.size(); i++) {
    //             if (sol[i] == c) {
    //                 index = i;
    //                 break;
    //             }
    //         }
    //         auto it = sol.begin() + index;
    //         while (num > 0) {
    //             sol.insert(it + 1, static_cast<char>(num % 10));
    //             num /= 10;
    //         }
    //     }
    // }

            // vector<char> sol;
        // sol.push_back(' '); // 0
        // sol.push_back('a'); // 1
        // sol.push_back(' '); // 2
        // sol.push_back(op1); // 3
        // sol.push_back(' '); // 4
        // sol.push_back('b'); // 5
        // sol.push_back(' '); // 6
        // sol.push_back(op2); // 7
        // sol.push_back(' '); // 8
        // sol.push_back('c'); // 9
        // sol.push_back(' '); // 10
        // sol.push_back(op3); // 11
        // sol.push_back(' '); // 12
        // sol.push_back('d'); // 13
        // sol.push_back(' '); // 14


*/
