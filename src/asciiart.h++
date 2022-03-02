
#include <iostream>
#include <string>
#include <unistd.h> /* For sleep(). */

#define MARGIN 500000

using namespace std;

class Title {

public:
	Title();
	string title_bio;
	string title_terminology;
	string title_quiz;
	void   showTitle();

};

Title::Title() {

	title_bio         = " ____  _       \n| __ )(_) ___  \n|  _ \\| |/ _ \\ \n| |_) | | (_) |\n|____/|_|\\___/ \n";
	title_terminology = " _____                   _             _                   \n|_   _|__ _ __ _ __ ___ (_)_ __   ___ | | ___   __ _ _   _ \n  | |/ _ \\ '__| '_ ` _ \\| | '_ \\ / _ \\| |/ _ \\ / _` | | | |\n  | |  __/ |  | | | | | | | | | | (_) | | (_) | (_| | |_| |\n  |_|\\___|_|  |_| |_| |_|_|_| |_|\\___/|_|\\___/ \\__, |\\__, |\n                                               |___/ |___/ \n";
	title_quiz        = "  ___        _       _ \n / _ \\ _   _(_)____ | |\n| | | | | | | |_  / | |\n| |_| | |_| | |/ /  |_|\n \\__\\_\\\\__,_|_/___| (_)\n";

}

void Title::showTitle() {

	cout << title_bio;
	cout << title_terminology;
	cout << title_quiz;

}

class Ready {

public:
	Ready();
	string ready_three;
	string ready_two;
	string ready_one;
	string ready_go;
	void   countDown();
	void   areYouReady();

};

Ready::Ready() {

	ready_three = " _____ \n|___ / \n  |_ \\\n ___) |\n|____/ \n";
	ready_two   = " ____  \n|___ \\\n  __) |\n / __/ \n|_____|\n";
	ready_one   = " _     \n/ |    \n| |    \n| |    \n|_|    \n";
	ready_go    = "  ____         _ \n / ___| ___   | |\n| |  _ / _ \\  | |\n| |_| | (_) | |_|\n \\____|\\___/  (_)\n";

}

void Ready::countDown() {

	//int margin = 500000;

	cout << "\033[2J";
	cout << ready_three << endl;
	usleep( MARGIN );

	cout << "\033[6A";
	cout << ready_two << endl;
	usleep( MARGIN );

	cout << "\033[6A";
	cout << ready_one << endl;
	usleep( MARGIN );

	cout << "\033[6A";
	cout << "\033[1m";
	cout << "\033[32m";
	cout << ready_go << endl;
	usleep( MARGIN * 2 );

	cout << "\033[0m"; /* 標準属性に戻す */
	cout << "\033[39m"; /* 標準色に戻す */

	cout << "\033[2J";

}

void Ready::areYouReady() {

	cout << "\nARE YOU READY ?\n" << endl;
	cout << "Enter キーでスタート ! : ";

	getchar();
	getchar();

}
