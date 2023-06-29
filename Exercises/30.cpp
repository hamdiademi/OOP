//
// Created by Hamdi on 6/6/2023.
//
#include<iostream>
#include<cstring>

using namespace std;
class WrongLabelsFormatException{
public:
    void showMessage(){
        cout << "Labels must have the same length";
    }
};
class Evaluator{
protected:
    char trueLabel[101];
    char predictedLabel[101];
public:
    Evaluator(char *trueLabel, char *predictedLabel) {
        if (strlen(trueLabel)!=strlen(predictedLabel)){
            throw WrongLabelsFormatException();
        }
        strcpy(this->trueLabel,trueLabel);
        strcpy(this->predictedLabel,predictedLabel);
    }

    virtual double evaluate()=0;
    virtual void print()=0;


    bool operator>=(Evaluator &rhs) {
        return this->evaluate()>=rhs.evaluate();
    }
};
class AccuracyEvaluator: public Evaluator{

public:
    AccuracyEvaluator(char *trueLabel, char *predictedLabel) : Evaluator(trueLabel, predictedLabel) {}

    double evaluate() override {
        int count=0;
        for (int i = 0; i < strlen(trueLabel); ++i) {
            if (trueLabel[i]==predictedLabel[i]){
                count++;
            }
        }
        return count/strlen(trueLabel);
    }

    void print() override {
        //Number of data points: 4 Prediction Accuracy: 0.5
        cout << "Number of data points: " << strlen(trueLabel) << " Prediction Accuracy: " << evaluate() << endl;
    }

};
class SensitivityEvaluator: public Evaluator{
public:
    SensitivityEvaluator(char *trueLabel, char *predictedLabel) : Evaluator(trueLabel, predictedLabel) {}

    double evaluate() override {
        int count=0;
        int count_plus=0;
        for (int i = 0; i < strlen(trueLabel); ++i) {
            if (trueLabel[i]=='+'){
                count_plus++;
            }
            if (trueLabel[i]==predictedLabel[i]){
                count++;
            }
        }
        return count/count_plus;

    }

    void print() override {
        //Number of data points: 4 Prediction Accuracy: 0.5
        cout << "Number of data points: " << strlen(trueLabel) << " Prediction Sensitivity: " << evaluate() << endl;
    }


};

Evaluator* highestScore (Evaluator ** evaluators, int n){
    double max=0;
    int index=-1;
    for (int i = 0; i < n; ++i) {
        if (dynamic_cast<AccuracyEvaluator *>(evaluators[i])) {
            if (evaluators[i]->evaluate() >= max) {
                max = evaluators[i]->evaluate();
                index = i;
            }
        }
    }
    return evaluators[index];
}
//Evaluator *bestAccuracyEvaluator(Evaluator **evaluators, int n){
//    Evaluator *max= nullptr;
//    for (int i = 0; i < n; ++i) {
//        AccuracyEvaluator *casted=dynamic_cast<AccuracyEvaluator *>(evaluators[i]);
//        if (casted){
//            if (max == nullptr){
//                max = evaluators[i];
//            } else if (*(evaluators[i])>=(*max)){
//                max=evaluators[i];
//            }
//        }
//    }
//    return max;
//}

int main() {
    int testCase;
    char trueLabels[100];
    char predictedLabels[100];
    cin >> testCase;
    if (testCase == 1) {
        cout << "TESTING CREATION OF ACCURACY EVALUATOR. EXCEPTION CAN HAPPEN HERE!" << endl;
        cin >> trueLabels >> predictedLabels;

        try {
            Evaluator *evaluator = new AccuracyEvaluator(trueLabels, predictedLabels);
            cout << evaluator->evaluate() << endl;
            evaluator->print();
        } catch (WrongLabelsFormatException &e) {
            e.showMessage();
        }


    } else if (testCase == 2) {
        cout << "TESTING CREATION OF ACCURACY EVALUATOR. EXCEPTION CAN HAPPEN HERE!" << endl;
        cin >> trueLabels >> predictedLabels;

        try {
            Evaluator *evaluator = new SensitivityEvaluator(trueLabels, predictedLabels);
            cout << evaluator->evaluate() << endl;
            evaluator->print();
        } catch (WrongLabelsFormatException &e) {
            e.showMessage();
        }

    } else if (testCase == 3) {
        cout << "TESTING CREATION OF BOTH EVALUATORS. EXCEPTION CAN HAPPEN HERE!" << endl;
        cin >> trueLabels >> predictedLabels;

        try {
            Evaluator *accuracy = new AccuracyEvaluator(trueLabels, predictedLabels);
            Evaluator *sensitivity = new SensitivityEvaluator(trueLabels, predictedLabels);
            accuracy->print();
            sensitivity->print();
        } catch (WrongLabelsFormatException &e) {
            e.showMessage();
        }

    } else if (testCase == 4) {
        cout << "TESTING OPERATOR >=" << endl;
        cin >> trueLabels >> predictedLabels;
        Evaluator *accuracy = new AccuracyEvaluator(trueLabels, predictedLabels);
        Evaluator *sensitivity = new SensitivityEvaluator(trueLabels, predictedLabels);
        cin >> trueLabels >> predictedLabels;
        Evaluator *accuracy1 = new AccuracyEvaluator(trueLabels, predictedLabels);
        Evaluator *sensitivity1 = new SensitivityEvaluator(trueLabels, predictedLabels);

        accuracy->print();
        cout << (((*accuracy) >= (*sensitivity)) ? ">=" : "<") << endl;
        sensitivity->print();
        cout << endl;

        sensitivity->print();
        cout << (((*sensitivity) >= (*accuracy)) ? ">=" : "<") << endl;
        accuracy->print();
        cout << endl;

        accuracy->print();
        cout << (((*accuracy) >= (*accuracy1)) ? ">=" : "<") << endl;
        accuracy1->print();
        cout << endl;

        sensitivity->print();
        cout << (((*sensitivity) >= (*sensitivity1)) ? ">=" : "<") << endl;
        sensitivity1->print();
        cout << endl;
    } else {
        cout << "INTEGRATION TEST AND TESTING GLOBAL FUNCTION. EXCEPTION CAN HAPPEN HERE!" << endl;
        int n;
        cin >> n;
        Evaluator **evaluators = new Evaluator *[n];
        for (int i = 0; i < n; i++) {
            int type;
            cin >> type;
            cin >> trueLabels >> predictedLabels;

            try {
                if (type == 1) { //accuracy
                    evaluators[i] = new AccuracyEvaluator(trueLabels, predictedLabels);
                } else { //sensitivity
                    evaluators[i] = new SensitivityEvaluator(trueLabels, predictedLabels);
                }
            } catch (WrongLabelsFormatException &e) {
                e.showMessage();
                --n;
                --i;
            }


        }

        cout << "PRINT ALL EVALUATORS FIRST!" << endl;
        for (int i = 0; i < n; i++) {
            evaluators[i]->print();
        }

        cout << "RESULT FROM HIGHEST SCORE METHOD" << endl;
        highestScore(evaluators, n)->print();
    }

}