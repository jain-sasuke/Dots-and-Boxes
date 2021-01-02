#include <bits/stdc++.h>
#include "state.hpp"
#include "game.hpp"

using namespace std;

void play_game(game &g, int r, int c)
{
    cout << "Press 1 to play a 2 player game, 2 to play against an agent: ";
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        g.play();
    }
    else if (choice == 2)
    {
        cout << "Press 1 to play against a simple agent, 2 to play against a random agent and 3 to play against a pre-trained q-agent.\n";
        int ag_choice;
        cin >> ag_choice;
        if (ag_choice == 1)
        {
            simple_agent *sag = new simple_agent;
            g.play(sag);
            delete sag;
        }
        else if (ag_choice == 2)
        {
            random_agent *rag = new random_agent;
            g.play(rag);
            delete rag;
        }
        else if (ag_choice == 3)
        {
            ifstream fin;
            fin.open("dir" + to_string(r) + "x" + to_string(c), ios_base::in);
            if (!fin)
            {
                cout << "No pre-trained agents found. Aborting...\n";
                return;
            }
            vector<string> files;
            string temp;
            while (fin >> temp)
            {
                files.push_back(temp);
            }
            cout << "Enter the index of the q-agent to select it: " << endl;
            for (int k = 0; k < files.size(); k++)
            {
                cout << k + 1 << " " << files[k] << endl;
            }
            int file_no;
            cin >> file_no;
            if ((file_no > files.size()) || (file_no < 1))
            {
                cout << "Error! Invalid choice. Aborting..." << endl;
                return;
            }
            string file_name = files[file_no - 1];
            fin.close();
            q_agent *qag = new q_agent;
            ifstream finna;
            finna.open(file_name, ios_base::in);
            qag->read_file(finna);
            g.play(qag);
            delete qag;
            finna.close();
        }
        else
        {
            cout << "Error! Invalid choice. Aborting..." << endl;
        }
    }
    else
    {
        cout << "Error! Invalid choice. Aborting...\n";
    }
}

void train_agent(game &g, int r, int c)
{
    string name;
    cout << "Enter the name of the q_agent: ";
    cin >> name;
    cout << "Press 1 to train a new agent, 2 to train an existing agent: ";
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        cout << "Enter the learning rate: ";
        double lr;
        cin >> lr;
        cout << "Enter the discount: ";
        double discount;
        cin >> discount;
        cout << "Enter the value of epsilon: ";
        double epsilon;
        cin >> epsilon;
        epsilon *= 10;
        q_agent *qag = new q_agent;
        qag->set(r, c, discount, lr, (int)epsilon);
        cout << "Press 1 to choose a simple agent as the adversary, 2 to choose a random agent as the adversary, 3 to load a pre-trained q-learning agent and 4 to choose an untrained q-learning agent as the adversary: ";
        int ad_choice;
        cin >> ad_choice;
        agent *adversary;
        if (ad_choice == 1)
        {
            adversary = new simple_agent;
        }
        else if (ad_choice == 2)
        {
            adversary = new random_agent;
        }
        else if (ad_choice == 3)
        {

            ifstream fin;
            fin.open("dir" + to_string(r) + "x" + to_string(c), ios_base::in);
            if (!fin)
            {
                cout << "No pre-trained agents found. Aborting...\n";
                return;
            }
            vector<string> files;
            string temp;
            while (fin >> temp)
            {
                files.push_back(temp);
            }
            cout << "Enter the index of the q-agent to select it: " << endl;
            for (int k = 0; k < files.size(); k++)
            {
                cout << k + 1 << " " << files[k] << endl;
            }
            int file_no;
            cin >> file_no;
            if ((file_no > files.size()) || (file_no < 1))
            {
                cout << "Error! Invalid choice. Aborting..." << endl;
                return;
            }
            string file_name = files[file_no - 1];
            fin.close();
            adversary = new q_agent;
            ifstream finna;
            finna.open(file_name, ios_base::in);
            adversary->read_file(finna);
            finna.close();
        }
        else if (ad_choice == 4)
        {
            cout << "Enter the learning rate: ";
            cin >> lr;
            cout << "Enter the discount: ";
            cin >> discount;
            cout << "Enter the value of epsilon: ";
            cin >> epsilon;
            epsilon *= 10;
            adversary = new q_agent;
            adversary->set(r, c, discount, lr, epsilon);
        }
        else
        {
            cout << "Error! Invalid choice. Aborting...\n";
            delete qag;
            return;
        }
        auto results = g.train_stats(qag, adversary);
        ofstream main_dir;
        string dir = "dir";
        dir += to_string(r);
        dir += "x";
        dir += to_string(c);
        main_dir.open(dir, ios_base::app);
        if (!main_dir)
        {
            main_dir.open(dir, ios_base::out);
        }
        main_dir << name << endl;
        main_dir.close();
        ofstream res_file;
        res_file.open(name + ".csv", ios_base::out);
        res_file << "Iteration,WinRate" << endl;
        for (int i = 0; i < results.size(); i++)
        {
            res_file << i + 1 << "," << results[i] << endl;
        }
        res_file.close();
        ofstream q_file;
        q_file.open(name, ios_base::out);
        qag->write_file(q_file);
        q_file.close();
        delete qag;
    }
    else if (choice == 2)
    {
        ifstream fin;
        fin.open("dir" + to_string(r) + "x" + to_string(c), ios_base::in);
        if (!fin)
        {
            cout << "No pre-trained agents found. Aborting...\n";
            return;
        }
        vector<string> files;
        string temp;
        while (fin >> temp)
        {
            files.push_back(temp);
        }
        cout << "Enter the index of the q-agent to select it: " << endl;
        for (int k = 0; k < files.size(); k++)
        {
            cout << k + 1 << " " << files[k] << endl;
        }
        int file_no;
        cin >> file_no;
        if ((file_no > files.size()) || (file_no < 1))
        {
            cout << "Error! Invalid choice. Aborting..." << endl;
            return;
        }
        string file_name = files[file_no - 1];
        fin.close();
        q_agent *qag = new q_agent;
        ifstream finna;
        finna.open(file_name, ios_base::in);
        qag->read_file(finna);
        finna.close();

        cout << "Press 1 to choose a simple agent as the adversary, 2 to choose a random agent as the adversary and 3 to load a pre-trained q-learning agent: ";
        int ad_choice;
        cin >> ad_choice;
        agent *adversary;
        if (ad_choice == 1)
        {
            adversary = new simple_agent;
        }
        else if (ad_choice == 2)
        {
            adversary = new random_agent;
        }
        else if (ad_choice == 3)
        {

            ifstream fin;
            fin.open("dir" + to_string(r) + "x" + to_string(c), ios_base::in);
            if (!fin)
            {
                cout << "No pre-trained agents found. Aborting...\n";
                return;
            }
            vector<string> files;
            string temp;
            while (fin >> temp)
            {
                files.push_back(temp);
            }
            cout << "Enter the index of the q-agent to select it: " << endl;
            for (int k = 0; k < files.size(); k++)
            {
                cout << k + 1 << " " << files[k] << endl;
            }
            int file_no;
            cin >> file_no;
            if ((file_no > files.size()) || (file_no < 1))
            {
                cout << "Error! Invalid choice. Aborting..." << endl;
                return;
            }
            string file_name = files[file_no - 1];
            fin.close();
            adversary = new q_agent;
            ifstream finna;
            finna.open(file_name, ios_base::in);
            adversary->read_file(finna);
            finna.close();
        }
        else
        {
            cout << "Error! Invalid choice. Aborting...\n";
            delete qag;
            return;
        }
        auto results = g.train_stats(qag, adversary);
        ofstream main_dir;
        string dir = "dir";
        dir += to_string(r);
        dir += "x";
        dir += to_string(c);
        main_dir.open(dir, ios_base::app);
        if (!main_dir)
        {
            main_dir.open(dir, ios_base::out);
        }
        main_dir << name << endl;
        main_dir.close();
        ofstream res_file;
        res_file.open(name + ".csv", ios_base::out);
        res_file << "Iteration,WinRate" << endl;
        for (int i = 0; i < results.size(); i++)
        {
            res_file << i + 1 << "," << results[i] << endl;
        }
        res_file.close();
        ofstream q_file;
        q_file.open(name, ios_base::out);
        qag->write_file(q_file);
        q_file.close();
        delete qag;
    }
    else
    {
        cout << "Error! Inavlid choice. Aborting...\n";
    }
}

int main()
{
    /*int rows, cols;
    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> cols;
    state_matrix st;
    st.set(rows, cols);
    for (int i = 0; i < 16; i++)
    {
        st.set_state(i);
        st.print();
    }*/

    srand(time(NULL)); //seed for random agent

    game g;

    bool ex = false;
    cout << "Welcome! Enter the no of rows in the grid: ";
    int r;
    cin >> r;
    cout << "Enter the number of columns in the grid: ";
    int c;
    cin >> c;
    cout << "Initialising grid..." << endl;
    g.set(r, c);
    do
    {
        cout << "Enter 1 to play a game, 2 to train an agent: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            g.reset();
            play_game(g, r, c);
            break;
        case 2:
            g.reset();
            train_agent(g, r, c);
            break;
        default:
            cout << "Error! Invalid value entered.\n";
        }
        cout << "Enter Y to continue, N to exit: ";
        char excheck;
        cin >> excheck;
        if (excheck == 'N' || excheck == 'n')
        {
            ex = true;
        }
        else if (excheck == 'Y' || excheck == 'y')
        {
            ex = false;
        }
        else
        {
            ex = true;
        }

    } while (!ex);

    return 0;

    g.set(3, 3);
    simple_agent *sag = new simple_agent;
    random_agent *rag = new random_agent;
    q_agent *q1 = new q_agent;
    //q1->set(3, 3, 0.2, 0.8);
    q_agent *q2 = new q_agent;
    //q2->set(3, 3, 0.8, 0.2);
    q_agent *qag = new q_agent;
    //qag->set(3, 3, 0.8, 0.2);
    q_agent *q3 = new q_agent;
    //q3->set(3, 3, 0.8, 0.2);
    q_agent *q4 = new q_agent;
    //q4->set(3, 3, 0.8, 0.2);
    //g.play(rag);
    /*int q_count = 0;
    int ran_count = 0;
    for (int i = 0; i < 100000; i++)
    {
        qag->reset();
        qag2->reset();
        auto p = g.train(qag, sag);
        //q_count += p.first;
        //ran_count += p.second;
        g.reset();
    }
    for (int i = 0; i < 100000; i++)
    {
        qag->reset();
        qag2->reset();
        auto p = g.test(qag, sag);
        q_count += p.first;
        ran_count += p.second;
        g.reset();
    }
    cout << "Q agent wins: " << q_count << endl;
    cout << "Random agent wins: " << ran_count << endl;
    //qag->print_q_values();
    */
    auto res = g.train_stats(q1, rag);
    /*int count = 1;
    for (auto i : res)
    {
        cout << count << "," << i << endl;
        count++;
    }*/
    //int count = 1;
    auto res2 = g.train_stats(q2, qag);
    /*for (auto i : res2)
    {
        cout << count << "," << i << endl;
        count++;
    }*/
    //auto res3 = g.train_stats(q3, sag);
    /*for (auto i : res3)
    {
        //cout << i << endl;
    }*/
    //int count = 1;
    //auto res4 = g.train_stats(q1, qag);
    /*for (auto i : res4)
    {
        cout << count << "," << i << endl;
        count++;
    }*/
    /*auto res5 = g.train_stats(q2, rag);
    int count = 1;
    for (auto i : res5)
    {
        cout << count << "," << i << endl;
        count++;
    }*/
    /*auto res6 = g.train_stats(q1, q2);
    int count = 1;
    for (auto i : res6)
    {
        cout << count << "," << i << endl;
        count++;
    }*/
    /*auto res7 = g.train_stats(q3, q1);
    int count = 1;
    for (auto i : res7)
    {
        cout << count << "," << i << endl;
        count++;
    }*/
    auto res8 = g.train_stats(q1, q2);
    int count = 1;
    for (auto i : res8)
    {
        cout << count << "," << i << endl;
        count++;
    }
    delete sag;
    delete rag;
    delete q1;
    delete q2;
    delete q3;
    delete q4;
    delete qag;
    return 0;
}