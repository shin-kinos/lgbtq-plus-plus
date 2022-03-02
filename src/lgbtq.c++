
#include <chrono> /* For elapse time. */
#include <iostream>
#include <vector>

#include "settings.h++"
#include "asciiart.h++"
#include "file.h++"
#include "question.h++"
#include "result.h++"

using namespace std;

int main() {

	/* Show quiz title. */
	Title title;
	title.showTitle();
	//title.~Title();

	/* Read quiz file. */
	Question data;
	data.getFileData();

	/* Show data. */
	//data.showData();

	/* Quiz settings. */
	Settings settings;
	settings.setDifficulty();
	int difficulty = settings.getDifficulty();

	/* Show unit name. */
	data.showUnitList();

	/* Set unit list by user. */
	settings.setUnitList();

	/* Sort and purify the unit list. */
	settings.sortAndUniq();

	vector<int> unit_list = settings.getUnitList();

	/* Pick up selected unit list */
	data.pickUpLevel( difficulty );

	/* Make question list. */
	if ( unit_list[ 0 ] != 0 ) data.makeQuestionList( unit_list );

	data.showQuestionList();

	Ready ready;
	ready.areYouReady();
	ready.countDown();

	/* Make radomized question list. */
	data.randomizeQlist();

	/* Elapse time : START. */
	chrono::system_clock::time_point time_start, time_end;
	time_start = std::chrono::system_clock::now();

	/* Start quiz. */
	data.doQuiz();

	/* Elape time : END. */
	time_end = chrono::system_clock::now();
	double elapsed_time = chrono::duration_cast<chrono::milliseconds>( time_end - time_start).count();
	elapsed_time = elapsed_time / 1000;
	//cout << "Elapse time : " << elapsed_time << " sec";

	/* Show result. */
	show_result(
		( data.word_jp ),
		( data.word_en ),
		( data.q_number_random ),
		( data.your_answers_index ),
		elapsed_time
		);

	return 0;
}
