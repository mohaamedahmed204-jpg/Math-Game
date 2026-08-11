#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

enum enQuestionsLevel {Easy = 1, Medium = 2, Hard = 3, Insane = 4};
enum enOperationType {Add = 1, Subtract = 2, Multiply = 3, Division = 4, Mix = 5};

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

struct stQuizzResults
{
    int NumberOfQuestions = 0;
    
    enQuestionsLevel QuesLevel;
    enOperationType Op;
    
    int RightAnswer = 0;
    int WrongAnswer = 0;
    
};

// The main struct for the game
struct stQuizz
{
    float Number1 = 0;
    int Number2 = 0;
    float Answer = 0;
    char CurrentOp;
};

int RandomNumber(int From, int To)
{
    int randnum = rand() % (To - From + 1) + From;
    return randnum;
}

void ClearBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int ReadNumberOfQuestions(string message)
{
    int Questions;
    cout << message;
    
    while(true)
    {
        cin >> Questions;

        // Keep it save if the input was a string
        if(cin.fail() || cin.peek() != '\n')
        {
            ClearBuffer();
            cout << "Entre Only a positive Number: ";
        }
        else if(Questions < 1 || Questions > 100)
        {
            cout << "Entre Only a positive Number, and not more than 100 Questions: ";
        }
        else 
            return Questions;
    }
}

enQuestionsLevel ReadQuestionsLevel(string message)
{
    int Level;
    cout << message;
    
    while(true)
    {
        cin >> Level;
        
        if(cin.fail() || cin.peek() != '\n')
        {
            ClearBuffer();
            cout << "Entre Only a positive Number: ";
        }
        else if(Level < 1 || Level > 4)
        {
            ClearBuffer();
            cout << "Entre Only a Number Between 1 and 4: ";
        }
        else 
            return (enQuestionsLevel)Level;
    }
}

enOperationType ReadOperationType(string message)
{
    int Type;
    cout << message;
    
    while(true)
    {
        cin >> Type;
        
        if(cin.fail() || cin.peek() != '\n')
        {
            ClearBuffer();
            cout << "Entre Only a positive Number: ";
        }
        else if(Type < 1 || Type > 5)
        {
            ClearBuffer();
            cout << "Entre Only a Number Between 1 and 5: ";
        }
        else 
            return (enOperationType)Type;
    }
}

char PlayAgain()
{
    char Continue;
    cout << "Do you want another Quizz? Y/N? ";
    
    while(true)
    {
        cin >> Continue;
        Continue = toupper(Continue);
        
        if((Continue != 'Y' && Continue != 'N') || cin.peek() != '\n')
        {
            ClearBuffer();
            cout << "Entre Only Y Or N ";
        }
        else{
            cout << '\n';
            return Continue;
        }
    }
}

string DeterminePassOrFail(stQuizzResults &QuizzData)
{
   return (QuizzData.RightAnswer < QuizzData.WrongAnswer ? "Fail :(" : "Pass :)");
}

string DetermineQuesLevel(enQuestionsLevel Level)
{
    string levels[] {"Easy", "Medium", "Hard", "Insane"};
    
    return levels[Level - 1];
}

string DetermineOperationSymbol(enOperationType Op)
{
    string Operation[] {"Add", "Subtract", "Multiply", "Division", "Mix"};
    
    return Operation[Op - 1];
}

char DetermineOperation(enOperationType Op)
{
    char Operation[] {'+', '-', '*', '/'};
    
    if(Op == enOperationType::Mix)
    {
        int RandOp = RandomNumber(1, 4);
        return Operation[RandOp - 1];
    }
    
    return Operation[Op - 1];
}

int AvoidZeros(int From, int To)
{
    int Num2;
    do{
        Num2 = RandomNumber(From, To);
    } while(Num2 == 0);
    
    return Num2;
}

void GenerateNumbers(stQuizz &Quizz, enQuestionsLevel &Level)
{
    switch(Level)
    {
        case enQuestionsLevel::Easy:
        {
            Quizz.Number1 = RandomNumber(-10, 10);
            Quizz.Number2 = AvoidZeros(-10, 10);
            break;
        }
        case enQuestionsLevel::Medium:
        {
            Quizz.Number1 = RandomNumber(-100, 100);
            Quizz.Number2 = AvoidZeros(-100, 100);
            break;
        }
        case enQuestionsLevel::Hard:
        {
            Quizz.Number1 = RandomNumber(-1000, 1000);
            Quizz.Number2 = AvoidZeros(-1000, 1000);
            break;
        }
        case enQuestionsLevel::Insane:
        {
            Quizz.Number1 = RandomNumber(-10000, 10000);
            Quizz.Number2 = AvoidZeros(-10000, 10000);
            break;
        }
    }
}

float SimpleCalculator(float Num1, int Num2, char CurrentOp)
{
    switch(CurrentOp)
    {
        case '+': return Num1 + Num2;
        case '-': return Num1 - Num2;
        case '*': return Num1 * Num2;
        case '/': return Num1 / Num2;
    }
    return 1.0;
}

string DetermineAnswer(stQuizz &Quizz, stQuizzResults &QuizzData)
{
    float RightAnswer = SimpleCalculator(Quizz.Number1, Quizz.Number2, Quizz.CurrentOp);
    
    if(abs(Quizz.Answer - RightAnswer) < 0.01)
    {
        QuizzData.RightAnswer++;
        return "Right Answer !!";
    }
    else
    {   QuizzData.WrongAnswer++;
        return "Wrong Answer \nThe Right Answer is: " +
        (abs(RightAnswer - (int)RightAnswer) > 0 ? to_string(RightAnswer) : to_string((int)RightAnswer));
    }
}

void StartQuizz(stQuizz &Quizz, stQuizzResults &QuizzData)
{
    GenerateNumbers(Quizz, QuizzData.QuesLevel);
    Quizz.CurrentOp = DetermineOperation(QuizzData.Op);
    
    cout << Quizz.Number1 << '\n';
    cout << Quizz.Number2 << " " << Quizz.CurrentOp << '\n';
    cout << "\n-----------------\n";
    
    cin >> Quizz.Answer;
    cout << DetermineAnswer(Quizz, QuizzData) << "\n\n";
}

string Tabs(short NumberOfTabs)
{
    string t = "";
    while(NumberOfTabs--)
    {
        t += "\t";
    }
    return t;
}

void ShowQuizzOverScreen(stQuizzResults &QuizzData)
{
    cout << Tabs(4) << "-------------------------------------------------------------------------\n\n";
    cout << Tabs(7) << "Final Result is "<< DeterminePassOrFail(QuizzData) << "\n\n";
    cout << Tabs(4) << "-------------------------------------------------------------------------\n\n";
}

void ShowFinalQuizzResults(stQuizzResults &QuizzData)
{
    cout << Tabs(4) << "---------------------------[Quizz Results]-------------------------------\n\n";
    
    cout << Tabs(4) << "Number of Questions    : " << QuizzData.NumberOfQuestions << '\n';
    cout << Tabs(4) << "Questions Level        : " << DetermineQuesLevel(QuizzData.QuesLevel) << '\n';
    
    cout << Tabs(4) << "Operation Type         : " << DetermineOperationSymbol(QuizzData.Op) << '\n';
    
    cout << Tabs(4) << "Number of Right Answer : " << QuizzData.RightAnswer << '\n';
    cout << Tabs(4) << "Number of Wrong Answer : " << QuizzData.WrongAnswer << '\n';
    
    cout << "\n\n" << Tabs(4) << "-------------------------------------------------------------------------\n\n";
}

void PrintQuizzResults(stQuizzResults &QuizzData)
{
    ShowQuizzOverScreen(QuizzData);
    ShowFinalQuizzResults(QuizzData);
}

stQuizzResults AttemptQuizz()
{
    stQuizzResults QuizzData;
    stQuizz Quizz; 
    
    QuizzData.NumberOfQuestions = ReadNumberOfQuestions("How many Questions do you want to answer?\nNot more than 100 Questions: ");
    
    QuizzData.QuesLevel = ReadQuestionsLevel("\nEnter Question Level [1]:Easy, [2]:Medium, [3]:Hard, [4]:Insane ? ");
    
    QuizzData.Op = ReadOperationType("\nEnter Operation Type [1]:Add, [2]:Subtract, [3]:Multiply, [4]:Division, [5]:Mix ? ");
    
    for(int Question = 1; Question <= QuizzData.NumberOfQuestions; Question++)
    {
        cout << "\nQuestion [" << Question << "/" << QuizzData.NumberOfQuestions << "]\n\n";
        
        StartQuizz(Quizz, QuizzData);
    }
    
    return QuizzData;
}

void MathQuestions()
{
    do
    {
        system("clear");
        ResetScreen();
        
        cout << "\n\n" << Tabs(6) << "*** Welcome to the Arithmetic Questions Quizz!! ***\n\n";
        
        stQuizzResults QuizzData = AttemptQuizz();
        
        PrintQuizzResults(QuizzData);
        
    } while(PlayAgain() == 'Y');
    
    cout << '\n' << Tabs(6) << "*** Thank you for Attempt my Quizz. ***";
}

int main(void) {
    srand((unsigned)time(NULL));
    
    MathQuestions();
    return 0;
}
