#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <cctype>
#include <thread>
#include <algorithm>
using namespace std;

class Login //Class with all the login elements needed
{
public:
	string Username, Password, SecurityCode;
};

class SignIn //Class with all the sign in elements needed
{
public:
	string Username, Password, Gmail, SecurityCode, Age, ConfirmPassword;
};

string SecurityCodePrint() //Function which prints out a random three digit number
{
	int a;
	srand(chrono::high_resolution_clock::now().time_since_epoch().count());
	a = 100 + rand() % 900;
	return to_string(a);
}

bool isOnlyDigits(const string input) 	// Check if all characters in the input are digits
{
	return !input.empty() && std::all_of(input.begin(), input.end(), ::isdigit);
}

int main() //The main function ofc
{
	//All the variables needed
	string a;
	string CheckPass;
	string email;
	bool isValid = false;
	bool valid = true;
	int checkAge;

	cout << "Hello user, please type A/a for the sign in (New users) and B/b for the log in (Existing Users) procedure!" << endl; //Greets the user ofc

	while (true) //Checks if input is valid and corresponds to all three possible scenarios (A, B, Invalid input)
	{
		getline(cin, a); //getline instead of cin to include possible spaces written by the user

		if (a == "A" || a == "a") //Starts the sign in procedure
		{
			valid = false;

			SignIn NewUser;

			cout << "Welcome to our app new user! To begin the sign in procedure, please enter the username you wish to be called: ";

			while (!isValid)
			{
				getline(cin, NewUser.Username);

				if (NewUser.Username.length() > 16) //First checks if it's too long
				{
					cout << "Usernames can be up to 16 characters long! Please try again: ";
				}
				else if (NewUser.Username.length() < 4) //Then it checks if it's too short
				{
					cout << "Usernames must be at least 4 characters long! Please try again: ";
				}
				else //Now starts checking if username contains spaces or special characters
				{
					if (all_of(NewUser.Username.begin(), NewUser.Username.end(), [](char c)
						{ return isalnum(c); }))
					{
						cout << NewUser.Username << "... Hmmmm... Great choice!" << endl;
						break;
					}
					else
					{
						cout << "The username contains spaces or special characters! Please try again: ";
					}
				}
			}

			valid = true; //Valid goes back to true for future validations, next up comes the user choosing his password
			cout << "Next up, please choose your password (From 8 to 16 characters!): ";

			while (valid)
			{
				getline(cin, NewUser.Password);

				if (NewUser.Password.length() > 16) //First checks the length of the password
				{
					cout << "Passwords can be up to 16 characters long! Please try again: ";
					valid = true;
				}
				else if (NewUser.Password.length() < 8)
				{
					cout << "Passwords must be at least 8 characters long! Please try again: ";
					valid = true;
				}
				else
				{
					if (NewUser.Password.find(" ") != string::npos) //Then checks to see if it has any spaces
					{
						cout << "The password contains spaces! Please try again: ";
					}
					else
					{
						cout << endl << "Please confirm your password: "; //User must confirm his password

						while (valid)
						{
							getline(cin, NewUser.ConfirmPassword);

							if (NewUser.Password == NewUser.ConfirmPassword) //Checks the matching
							{
								cout << endl;
								cout << "Your password has been successfully set as " << NewUser.ConfirmPassword << "" << endl << endl; //Sets the user's password
								break;
							}
							else
							{
								cout << "Passwords do not match! Please try again: ";
							}
						}
					}

					break;
				}
			}

			valid = true;
			cout << "Please enter your age: "; //Must check user's age

			while (valid)
			{
				getline(cin, NewUser.Age);

				if (isOnlyDigits(NewUser.Age))
				{
					checkAge = stoi(NewUser.Age);

					if (checkAge < 14) //If too young, terminates the process
					{
						cout << "Must be at least 14 to use the app! Terminating sign in process..." << endl;
						this_thread::sleep_for(chrono::seconds(3));
						exit(0);
					}
					else if (checkAge > 120) //If too old, terminates the process
					{
						cout << "You're older than the oldest person that has ever lived? Nice try..." << endl;
						this_thread::sleep_for(chrono::seconds(3));
						exit(0);
					}
					else if (14 <= checkAge <= 120) //If valid, continues
					{
						cout << "Great! Thanks for confirming your age!" << endl;
						break;
					}
				}
				else
				{
					cout << "A non number character has been inputted! Please try again: ";
				}
			}

			valid = true; //Valid is true again, as we now ask the user to enter his email adress for authentication
			cout << endl;
			cout << "You're almost done! Lastly, please enter your email which we can use to send you authentication codes!" << endl;
			cout << "(Please note that we only accept these domains: @gmail.com, @yahoo.com, @aol.com, @outlook.com, @hotmail.com)" << endl;
			cout << endl;

			while (valid)
			{
				getline(cin, NewUser.Gmail);

				if (NewUser.Gmail.find("@gmail.com") != string::npos || //Checks if the email adress if of valid domain
					NewUser.Gmail.find("@yahoo.com") != string::npos ||
					NewUser.Gmail.find("@hotmail.com") != string::npos ||
					NewUser.Gmail.find("@outlook.com") != string::npos ||
					NewUser.Gmail.find("@aol.com") != string::npos)
				{
					if (NewUser.Gmail.find(" ") != string::npos)
					{
						cout << "Email adress contains spaces! Please try again: "; //Checks if the email adress has spaces
					}
					else
					{
						break; //Breaks if all the requirements are met
					}
				}
				else
				{
					cout << "Invalid email domain or email domain cannot be accepted! Please try again: ";
				}
			}

			cout << "Great! You are almost done!" << endl;
			cout << "We have sent a 3-digit security code for authentication to " << NewUser.Gmail << "!" << endl;
			cout << "Automatically opening Gmail app, please wait..." << endl;
			cout << endl;
			this_thread::sleep_for(chrono::seconds(5));

			NewUser.SecurityCode = SecurityCodePrint();
			cout << "----- YOUR SECURITY CODE IS " << NewUser.SecurityCode << "! -----" << endl << "This code will expire in 10 minutes!" << endl << "Code automatically copied! Going back, please wait.." << endl << endl;
			this_thread::sleep_for(chrono::seconds(5));

			cout << "Please type in your security code: ";
			valid = true;

			while (valid)
			{
				string SecurityCodeCheck;
				getline(cin, SecurityCodeCheck);

				if (SecurityCodeCheck == NewUser.SecurityCode)
				{
					cout << endl << "!!! SIGN IN SUCCESSFUL !!!" << endl;
					cout << "!!! ENJOY YOUR STAY " << NewUser.Username << " !!!";
					break;
				}
				else
				{
					cout << "Invalid security code, please try again: ";
				}
			}
			break;
		}
		else if (a == "B" || a == "b") //Starts the login procedure
		{
			valid = false;

			Login ExistingUser;

			cout << "Welcome back! Please enter your username: ";

			while (!isValid) //Checks if the username is of valid format
			{
				getline(cin, ExistingUser.Username); //getline instead of cin to include possible spaces written by the user

				if (ExistingUser.Username.length() > 16) //First checks if it's too long
				{
					cout << "Usernames can be up to 16 characters long! Please try again: ";
				}
				else if (ExistingUser.Username.length() < 4) //Then it checks if it's too short
				{
					cout << "Usernames must be at least 4 characters long! Please try again: ";
				}
				else //Now starts checking if username contains spaces or special characters
				{
					if (all_of(ExistingUser.Username.begin(), ExistingUser.Username.end(), [](char c)
						{ return isalnum(c); }))
					{
						break;
					}
					else
					{
						cout << "The username contains spaces or special characters! Please try again: ";
					}
				}
			}

			valid = true;
			cout << endl;
			cout << "Welcome back, " << ExistingUser.Username << ", please enter your password: ";

			while (valid)
			{
				getline(cin, ExistingUser.Password);

				if (ExistingUser.Password.length() > 16)
				{
					cout << "Passwords can be up to 16 characters long! Please try again: ";
					valid = true;
				}
				else if (ExistingUser.Password.length() < 8)
				{
					cout << "Passwords must be at least 8 characters long! Please try again: ";
					valid = true;
				}
				else
				{
					if (ExistingUser.Password.find(" ") == string::npos)
					{
						valid = false;
						break;
					}
					else
					{
						cout << "The password contains spaces! Check for any typos: ";
					}
				}
			}

			cout << endl;
			cout << "Great! You are almost done!" << endl;
			cout << "We have sent a 3-digit security code for authentication!" << endl;
			cout << "Automatically opening Gmail app, please wait..." << endl;
			cout << endl;
			this_thread::sleep_for(chrono::seconds(5));

			ExistingUser.SecurityCode = SecurityCodePrint();
			cout << "----- YOUR SECURITY CODE IS " << ExistingUser.SecurityCode << "! -----" << endl << "This code will expire in 10 minutes!" << endl << "Code automatically copied! Going back, please wait.." << endl << endl;
			this_thread::sleep_for(chrono::seconds(5));

			cout << "Please type in your security code: ";
			valid = true;

			while (valid)
			{
				string SecurityCodeCheck;
				getline(cin, SecurityCodeCheck);

				if (SecurityCodeCheck == ExistingUser.SecurityCode)
				{
					cout << endl << "!!! LOGIN SUCCESSFUL !!!" << endl;
					break;
				}
				else
				{
					cout << "Invalid security code, please try again: ";
				}
			}
			break;
		}
		else
		{
			valid = true;
			cout << "Invalid response, please answer with a valid character!" << endl;
		}
	}

	system("pause");
}