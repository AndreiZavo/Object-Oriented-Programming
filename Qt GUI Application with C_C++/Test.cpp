#include <cassert>
#include <fstream>
#include <cstdio>
#include "Service.h"
#include "Test.h"


void test_toString__valid_input__returns_string_of_date_first_case() {
	Date date{ 5, 6, 2000 };
	assert(date.toString() == "05-06-2000");
}

void test_toString__valid_input__returns_string_of_date_second_case() {
	Date date{ 15, 6, 2000 };
	assert(date.toString() == "15-06-2000");
}

void test_toString__valid_input__returns_string_of_date_third_case() {
	Date date{ 5, 16, 2000 };
	assert(date.toString() == "05-16-2000");
}

void test_toString__valid_input__returns_string_of_date_forth_case() {
	Date date{ 15, 16, 2000 };
	assert(date.toString() == "15-16-2000");
}

void test_getTitle__valid_input__returns_title() {
	Recording recording{ "aaa", "bbb", Date(1,4,2000), 5, "zzz" };
	assert(recording.getTitle() == "aaa");
}

void test_getFilmedAt__valid_input__returns_filmedAt() {
	Recording recording{ "aaa", "bbb", Date(1,4,2000), 5, "zzz" };
	assert(recording.getFilmedAt() == "bbb");
}

void test_getCreationDate__valid_input__returns_creationDate() {
	Recording recording{ "aaa", "bbb", Date(1,4,2000), 5, "zzz" };
	assert(recording.getCreationDate().toString() == "01-04-2000");
}

void test_getFootagePreview__valid_input__returnsFootagePreview() {
	Recording recording{ "aaa", "bbb", Date(1,4,2000), 5, "zzz" };
	assert(recording.getFootagePreview() == "zzz");
}

void test_toString__valid_input__returns_a_string_display_of_entity() {
	std::string expectedResult = "Title: aaa\n\tFilmed at: bbb\n\tCreation date: 01-04-2000\n\tAccess Count: 5\n\tFootage Preview: zzz\n";
	Recording recording{ "aaa", "bbb", Date(1,4,2000), 5, "zzz" };
	assert(recording.toString() == expectedResult);
}

void test_addElement__valid_input__correct_addition() {
	Repository repository{ "test.txt" };
	Saved_Repository savedRepository{ "test.txt" };
	Service service{ repository, savedRepository, "A" };
	service.addElement("aaa", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	assert(repository.getSize() == 1);
	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void test_addElement__duplicate_input__return_position_of_element() {
	Repository repository{ "test.txt" };
	Saved_Repository savedRepository{ "test.txt" };
	Service service{ repository, savedRepository, "A" };
	service.addElement("aaa", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	int resultOfAddition = service.addElement("aaa", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	assert(resultOfAddition == 0);
	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void test_addElement__invalid_access_mode__return_error_value() {
	Repository repository{ "test.txt" };
	Saved_Repository savedRepository{ "test.txt" };
	Service service{ repository, savedRepository, "B" };
	int result = service.addElement("aaa", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	assert(result == -8);
	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void test_updateElement__valid_input__correct_update() {
	Repository repository{ "test.txt" };
	Saved_Repository savedRepository{ "test.txt" };
	Service service{ repository, savedRepository, "A" };
	service.addElement("aaa", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	service.updateElement("aaa", "rrrr", Date::stringToDate("01-04-2020"), 5, "zzz");
	assert(service.getFileRepository().getElements()[0].getFilmedAt() == "rrrr");
	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void test_updateElement__valid_input__return_error_value() {
	Repository repository{ "test.txt" };
	Saved_Repository savedRepository{ "test.txt" };
	Service service{ repository, savedRepository, "A" };
	service.addElement("abc", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	int result = service.updateElement("aaa", "rrrr", Date::stringToDate("01-04-2020"), 5, "zzz");
	assert(result == -1);
	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void test_updateElement__invalid_access_mode__return_error_value() {
	Repository repository{ "test.txt" };
	Saved_Repository savedRepository{ "test.txt" };
	Service service{ repository, savedRepository, "B" };
	service.addElement("abc", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	int result = service.updateElement("aaa", "rrrr", Date::stringToDate("01-04-2020"), 5, "zzz");
	assert(result == -8);
	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void test_removeElement__valid_input__correct_removal() {
	Repository repository{ "test.txt" };
	Saved_Repository savedRepository{ "test.txt" };
	Service service{ repository, savedRepository, "A" };
	service.addElement("aaa", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	service.addElement("abc", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	service.removeElement("aaa");
	assert(repository.getSize() == 1);
	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void test_removeElement__valid_input__element_not_found() {
	Repository repository{ "test.txt" };
	Saved_Repository savedRepository{ "test.txt" };
	Service service{ repository, savedRepository, "A" };
	service.addElement("aaa", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	int result = service.removeElement("aba");
	assert(result == -1);
	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void test_removeElement__invalid_access_mode__return_error_value() {
	Repository repository{ "test.txt" };
	Saved_Repository savedRepository{ "test.txt" };
	Service service{ repository, savedRepository, "B" };
	service.addElement("aaa", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	int result = service.removeElement("aba");
	assert(result == -8);
	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void test_saveElement_valid_input__correct_save() {
	Repository repository{ "test.txt" };
	Saved_Repository savedRepository{ "test.txt" };
	Service service{ repository, savedRepository, "A" };
	service.addElement("aaa", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	service.setAccessMode("B");
	service.saveElement("aaa");
	assert(savedRepository.getSize() == 1);
	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void test_saveElement__valid_input__element_not_found() {
	Repository repository{ "test.txt" };
	Saved_Repository savedRepository{ "test.txt" };
	Service service{ repository, savedRepository, "A" };
	service.addElement("aaa", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	service.setAccessMode("B");
	int result = service.saveElement("aba");
	assert(result == -1);
	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void test_saveElement__invalid_access_mode__return_error_value() {
	Repository repository{ "test.txt" };
	Saved_Repository savedRepository{ "test.txt" };
	Service service{ repository, savedRepository, "A" };
	service.addElement("aaa", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	int result = service.saveElement("aba");
	assert(result == -8);
	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void test_nextElement__valid_input__correct_return_and_advance() {
	Repository repository{ "test.txt" };
	Saved_Repository savedRepository{ "test.txt" };
	Service service{ repository, savedRepository, "A" };
	service.addElement("aaa", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	service.setAccessMode("B");
	Recording record = service.next();
	assert(record.getTitle() == "aaa");
	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void test_nextElement__invalid_access_mode__return_error_value() {
	Repository repository{ "test.txt" };
	Saved_Repository savedRepository{ "test.txt" };
	Service service{ repository, savedRepository, "A" };
	service.addElement("aaa", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	Recording record = service.next();
	assert(record.getTitle() == "");
	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void test_nextElement__valid_input__cycling_to_the_first_element() {
	Repository repository{ "test.txt" };
	Saved_Repository savedRepository{ "test.txt" };
	Service service{ repository, savedRepository, "A" };
	service.addElement("aaa", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	service.addElement("abc", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	service.setAccessMode("B");
	Recording recording = Recording();
	for (int index = 0; index < 2; index++) {
		recording = service.next();
	}
	assert(recording.getTitle() == "abc");
	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void test_setFileName__valid_input__creation_of_filename() {
	char fileToDelete[] = "C:\delete.txt";
	Repository repository{ "test.txt" };
	Saved_Repository savedRepository{ "test.txt" };
	Service service{ repository, savedRepository, "A" };
	service.setFileName(fileToDelete);
	assert(savedRepository.getFilename() == fileToDelete);
	remove(fileToDelete);
}

void test_setAccessMode__invalid_input__return_error_value() {
	Repository repository{ "test.txt" };
	Saved_Repository savedRepository{ "test.txt" };
	Service service{ repository, savedRepository, "A" };
	service.addElement("aaa", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	service.addElement("abc", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	bool result = service.setAccessMode("C");
	assert(result == false);
	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void test_getElements__valid_input__correct_return_of_existing_elements_in_savedRepository() {
	Repository repository{ "test.txt" };
	Saved_Repository savedRepository{ "test.txt" };
	Service service{ repository, savedRepository, "A" };
	service.addElement("aaa", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	service.setAccessMode("B");
	service.saveElement("aaa");
	std::vector<Recording> savedRecordings = service.getAllElementsFromSavedRepository();
	assert(savedRecordings.size() == 1);
	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void test_getAllElementsFromFileRepository__valid_input__correct_return_of_existing_elements_in_FileRepository() {
	Repository repository{ "test.txt" };
	Saved_Repository savedRepository{ "test.txt" };
	Service service{ repository, savedRepository, "A" };
	service.addElement("aaa", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	std::vector<Recording> recordings = service.getAllElementsFromFileRepository();
	assert(recordings.size() == 1);
	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void test_getAccessMode__valid_input__correct_return_of_access_mode() {
	Repository repository{ "test.txt" };
	Saved_Repository savedRepository{ "test.txt" };
	Service service{ repository, savedRepository, "A" };
	std::string mode = service.getAccessMode();
	assert(mode == "A");

}
void test_undo__valid_input__correct_deletion_of_element_added() {
	Repository repository{ "test.txt" };
	Saved_Repository mylistRepository{ "test.txt" };
	Service service{ repository, mylistRepository, "A" };
	service.addElement("aaa", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	service.addElement("aba", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	service.undo();
	assert(repository.getSize() == 1);
	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void test_redo__valid_input__correct_addition_of_element() {
	Repository repository{ "test.txt" };
	Saved_Repository mylistRepository{ "test.txt" };
	Service service{ repository, mylistRepository, "A" };
	service.addElement("aaa", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	service.addElement("aba", "bbb", Date::stringToDate("01-04-2020"), 5, "zzz");
	service.removeElement("aaa");
	service.undo();
	service.redo();
	assert(repository.getSize() == 1);
	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void testAll() {
	
	//Date testing
	test_toString__valid_input__returns_string_of_date_first_case();
	test_toString__valid_input__returns_string_of_date_second_case();
	test_toString__valid_input__returns_string_of_date_third_case();
	test_toString__valid_input__returns_string_of_date_forth_case();

	//Domain testing
	test_getTitle__valid_input__returns_title();
	test_getFilmedAt__valid_input__returns_filmedAt();
	test_getCreationDate__valid_input__returns_creationDate();
	test_getFootagePreview__valid_input__returnsFootagePreview();
	test_toString__valid_input__returns_a_string_display_of_entity();

	//Repository & Service testing

				//--------ADD--------//
	test_addElement__valid_input__correct_addition();
	test_addElement__duplicate_input__return_position_of_element();
	test_addElement__invalid_access_mode__return_error_value();

				//-------UPDATE-------//
	test_updateElement__valid_input__correct_update();
	test_updateElement__valid_input__return_error_value();
	test_updateElement__invalid_access_mode__return_error_value();

				//-------REMOVE-------//
	test_removeElement__valid_input__correct_removal();
	test_removeElement__valid_input__element_not_found();
	test_removeElement__invalid_access_mode__return_error_value();

				//--------SAVE-------//
	test_saveElement_valid_input__correct_save();
	test_saveElement__valid_input__element_not_found();
	test_saveElement__invalid_access_mode__return_error_value();

				//--------NEXT-------//
	test_nextElement__valid_input__correct_return_and_advance();
	test_nextElement__invalid_access_mode__return_error_value();
	test_nextElement__valid_input__cycling_to_the_first_element();

				//------UNDO-REDO----//
	test_undo__valid_input__correct_deletion_of_element_added();
	test_redo__valid_input__correct_addition_of_element();

	test_setFileName__valid_input__creation_of_filename();
	test_setAccessMode__invalid_input__return_error_value();
	test_getElements__valid_input__correct_return_of_existing_elements_in_savedRepository();
	test_getAllElementsFromFileRepository__valid_input__correct_return_of_existing_elements_in_FileRepository();
	test_getAccessMode__valid_input__correct_return_of_access_mode();
}