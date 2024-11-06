#include "game.h"

game::game()
{
	table = {
		{"Award", "Number    |"},
		{"500 credits", "1         |"},
		{"50 credits", "2         |"},
		{"10 free games", "1         |"},
		{"5 free games", "2         |"},
		{"+2 extra picks", "2         |"},
		{"+1 extra picks", "1         |"},
		{"Blank (no prize)", "5         |"},
		{"Stopper", "1         |"}
	};
}

void game::start()
{
	for (;;)
	{
		system("cls");
		cout << "1. Instruction" << endl;
		cout << "2. Start game" << endl;
        cout << "3. Simulation" << endl;
		cout << "4. End\n>> ";
		int choice = 0;
		cin >> choice;

		if (choice == 1)
		{
			system("cls");
			instruction();
		}
		else if (choice == 2)
		{
			system("cls");
			startGame();
		}
		else if (choice == 4)
		{
			cout << "Game ends.." << endl;
			break;
		}
        else if (choice == 3)
        {
            system("cls");
            simulation();
        }
		else if (choice < 1 || choice > 3)
		{
			cout << "Invalid. Please try again" << endl;
			continue;
		}
	}
	
}

void game::instruction()
{
	cout << "A screen will be presented with 15 objects to select." << endl;
	cout << "Before the start of the game, the objects are randomized and picked without replacement." << endl << endl;

	int columnWidth = 17;
	for (int i = 0; i < table.size(); i++)
	{
		cout << "-------------------------------" << endl;

		for (int j = 0; j < table[i].size(); j++) {
			cout << "| " << setw(columnWidth) << left << table[i][j];  // Align text to left with fixed width
		}
		cout << endl;
	}

	cout << "-------------------------------" << endl;
	cout << "Press any key to continue.." << endl;
	_getch();
}

void game::startGame()
{
    // 15 objects
    vector<string> objects = {
        "500 credits", "50 credits", "50 credits",
        "10 free games", "5 free games", "5 free games",
        "+2 extra picks", "+2 extra picks", "+1 extra pick",
        "Blank", "Blank", "Blank", "Blank", "Blank",
        "Stopper"
    };

    // set up random number generator
    random_device rd;
    mt19937 g(rd());

    // shuffle randomly
    shuffle(objects.begin(), objects.end(), g);

    // track which numbers are picked
    vector<bool> picked(15, false);

    // player has 3 picks
    int chance = 3;
    int choice = 0;

    // start picking
    while (chance > 0)
    {
        for (int i = 0; i < objects.size(); i++)
        {

            if (!picked[i])  // display only obejects that have not been picked
            {
                cout << "[" << i + 1 << "]  ";
            }
        }

        cout << endl << "You have " << chance << " chances left. Choose your number >> ";
        cin >> choice;

        if (choice < 1 || choice > objects.size() || picked[choice - 1])  // out of range or already picked object
        {
            cout << "Invalid choice. Try again" << endl << endl;
            continue;
        }

        picked[choice - 1] = true;  // set this object as picked


        Sleep(1000);
        cout << "You picked " << objects[choice - 1] << endl << endl;

        if (objects[choice - 1] == "+1 extra picks")
        {
            chance += 1;
            cout << "You got 1 extra pick !" << endl << endl;
        }
        else if (objects[choice - 1] == "+2 extra picks")
        {
            chance += 2;
            cout << "You got 2 extra picks !" << endl << endl;
        }
        else if (objects[choice - 1] == "5 free games")
        {
            cout << "You got " << objects[choice - 1] << endl;
            cout << "But BMM says it has no effect.. Sorry..." << endl << endl;
        }
        else if (objects[choice - 1] == "10 free games")
        {
            cout << "You got " << objects[choice - 1] << endl;
            cout << "But BMM says it has no effect.. Sorry..." << endl << endl;
        }
        else if (objects[choice - 1] == "Stopper")
        {
            cout << "The game ends..." << endl;
            cout << "Press any key to go back to main menu..";
            _getch();
            return;
        }

        chance--;
        if (chance == 0)
        {
            cout << "You lost all your chances.." << endl;
            cout << "Press any key to go back to main menu..";
            _getch();
        }
    }
}

void game::simulation()
{
    srand(time(NULL));

    cout << "Simulation is operating.." << endl;
    Sleep(700);
    cout << ". ";
    Sleep(700);
    cout << ". ";
    Sleep(700);
    cout << ". ";
    Sleep(700);
   

    const int SIMULATION = 10000;   // how many times for simulation
    double total_picks = 0;   // check the sum of all picks made over simulations
    double total_credits = 0;

    map<string, int> picked;   // track how many times each item is selected across all the simulations

    for (int i = 0; i < SIMULATION; i++)
    {
        vector<string> objects = {
        "500 credits", "50 credits", "50 credits",
        "10 free games", "5 free games", "5 free games",
        "+2 extra picks", "+2 extra picks", "+1 extra pick",
        "Blank", "Blank", "Blank", "Blank", "Blank",
        "Stopper"
        };

        random_device rd;
        mt19937 g(rd());
        shuffle(objects.begin(), objects.end(), g);

        int initial_picks = 3;
        int simul_picks = 0;  // check how many times each game runs
        bool game_over = false;

        while (initial_picks > 0 && !game_over)
        {
            int choice = rand() % objects.size();   // random number for simulations
            string selected_objects = objects[choice];
            objects.erase(objects.begin() + choice);   // remove the selected number
            simul_picks++;

            picked[selected_objects]++;

            if (selected_objects == "+1 extra games")
            {
                initial_picks += 1;
            }
            else if (selected_objects == "+2 extra games")
            {
                initial_picks += 2;
            }
            else if (selected_objects == "50 credits")
            {
                total_credits += 50;
            }
            else if (selected_objects == "500 credits")
            {
                total_credits += 500;
            }
            else if (selected_objects == "Stopper")
            {
                game_over = true;
            }
            initial_picks--;
        }
        total_picks += simul_picks;
    }
    cout << "\nSimulation has finished" << endl;
    Sleep(500);
    cout << "--------------------------" << endl << endl;
    cout << fixed << setprecision(8);

    cout << "1.What is the average number of picks the player will get?>> " << endl;
    cout << "a)Theoritical probabilities\n";
    cout << "   3 + {(1*1/15) + (2*2/15)} = 3.33333333" << endl;

    cout << endl << "b)Simulated probabilities\n";
    cout << "   " << total_picks / SIMULATION << endl << endl;

    cout << "2.What is the probability of selecting each of the following in the feature?>>" << endl;
    cout << "a)Theoritical probabilities\n";
    map<string, double> theo_prob = {
        {"500 credits", 1.0 / 15},
        {"50 credits", 2.0 / 15},
        {"10 free games", 1.0 / 15},
        {"5 free games", 2.0 / 15},
        {"+2 extra picks", 2.0 / 15},
        {"+1 extra picks", 1.0 / 15},
        {"Blank", 5.0 / 15},
        {"Stopper", 1.0 / 15}
    };
    for (const auto& item : theo_prob)
    {
        cout << "   " << item.first << ": " << item.second << endl;
    }

    cout << endl << "b)Simulated probabilities\n";
    for (const auto& item : picked)
    {
        cout << "   " << item.first << ": " << (static_cast<double>(item.second) / total_picks) << endl;
    }

    cout << endl << "3.What is the average number of credits awarded (from the first two entries in the above table) per feature?>>" << endl;
    cout << "a)Theoritical probabilities\n";
    cout << "   (50*2/15) + (500*1/15) = 40" << endl;

    cout << endl << "b)Simulated probabilities\n";
    cout << "   " << total_credits / SIMULATION << endl << endl;

    cout << "Press any key to go back to main menu..";
    _getch();
}
