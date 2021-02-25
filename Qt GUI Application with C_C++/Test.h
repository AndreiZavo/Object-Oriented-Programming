#pragma once

void test_toString__valid_input__returns_string_of_date_first_case();

void test_toString__valid_input__returns_string_of_date_second_case();

void test_toString__valid_input__returns_string_of_date_third_case();

void test_toString__valid_input__returns_string_of_date_forth_case();

void test_getTitle__valid_input__returns_title();

void test_getFilmedAt__valid_input__returns_filmedAt();

void test_getCreationDate__valid_input__returns_creationDate();

void test_getFootagePreview__valid_input__returnsFootagePreview();

void test_toString__valid_input__returns_a_string_display_of_entity();

void test_addElement__valid_input__correct_addition();

void test_addElement__duplicate_input__return_position_of_element();

void test_updateElement__valid_input__return_error_value();

void test_updateElement__invalid_access_mode__return_error_value();

void test_addElement__invalid_access_mode__return_error_value();

void test_updateElement__valid_input__correct_update();

void test_removeElement__valid_input__correct_removal();

void test_removeElement__valid_input__element_not_found();

void test_removeElement__invalid_access_mode__return_error_value();

void test_saveElement_valid_input__correct_save();

void test_saveElement__valid_input__element_not_found();

void test_saveElement__invalid_access_mode__return_error_value();

void test_nextElement__valid_input__correct_return_and_advance();

void test_nextElement__invalid_access_mode__return_error_value();

void test_nextElement__valid_input__cycling_to_the_first_element();

void test_setFileName__valid_input__creation_of_filename();

void test_setAccessMode__invalid_input__return_error_value();

void test_getElements__valid_input__correct_return_of_existing_elements_in_savedRepository();

void test_getAllElementsFromFileRepository__valid_input__correct_return_of_existing_elements_in_FileRepository();

void test_getAccessMode__valid_input__correct_return_of_access_mode();

void testAll();