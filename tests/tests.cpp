#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "../src/Parser.hpp"
#include "../src/Factory.hpp"
#include "../src/components/special/TrueComponent.hpp"
// Test that the Parser throws an error for an empty filename
using nts::Parser;


// -------------------------------------- PARSER TESTS -------------------------------------- //

Test(parser_tests, test_empty_filename) {
    cr_expect_throw(Parser(""), nts::Error, "File does not exist");
}

//valid file
Test(parser_tests, test_valid_file) {
    nts::Parser parser("tests/parseFilesTest/valid_1.nts");
    cr_assert(parser.getChipsets().size() > 0, "Chipsets should be parsed");
    cr_assert(parser.getLinks().size() > 0, "Links should be parsed");
}

// empty .links and .chipsets
Test(parser_tests, test_invalid_file_missing_links_chipsets) {
    cr_expect_throw(nts::Parser parser("tests/parseFilesTest/invalid_1.nts");, nts::Error, "Invalid chipset format");
}

// missing component name in .chipsets
Test(parser_tests, test_invalid_file_missing_comp_name) {
    cr_expect_throw(nts::Parser parser("tests/parseFilesTest/invalid_2.nts");, nts::Error, "Invalid chipset format");
}

// empty file
Test(parser_tests, test_empty_file) {
    cr_expect_throw(nts::Parser parser("tests/parseFilesTest/invalid_3.nts");, nts::Error, "Invalid chipset format");
}

// extra names
Test(parser_tests, test_valid_file_extra_names) {
    nts::Parser parser("tests/parseFilesTest/valid_3.nts");
    cr_assert(parser.getChipsets().size() > 0, "Chipsets should be parsed");
    cr_assert(parser.getLinks().size() > 0, "Links should be parsed");
}

// spaces between chipsets and links
Test(parser_tests, test_valid_file_with_spaces) {
    nts::Parser parser("tests/parseFilesTest/valid_2.nts");
    cr_assert(parser.getChipsets().size() > 0, "Chipsets should be parsed");
    cr_assert(parser.getLinks().size() > 0, "Links should be parsed");
}


// -------------------------------------- FACTORY TESTS -------------------------------------- //

Test(factory_tests, create_known_component) {
    nts::Factory factory;
    std::unique_ptr<nts::IComponent> component = factory.createComponent("4001");
    cr_assert_not_null(component.get(), "Factory should create a non-null component for a known type");
}

// Test that an exception is thrown for an unknown component type
Test(factory_tests, create_unknown_component) {
    nts::Factory factory;
    cr_assert_throw(factory.createComponent("unknown_type"), nts::Error, "Factory should throw an exception for an unknown component type");
}

// Test the creation of each known component type
Test(factory_tests, create_all_known_types) {
    nts::Factory factory;
    std::vector<std::string> knownTypes = {"4001", "4008", "4011", "4013", "4030", "4040", "4069", "4071", "4081", "4512", "input", "output", "true", "false", "clock", "or", "nor", "xor", "not", "and", "nand"};
    for (const auto& type : knownTypes) {
        cr_assert_no_throw(factory.createComponent(type), nts::Error, "Factory should successfully create component of type: %s", type.c_str());
    }
}

// -------------------------------------- SPECIAL COMPONENTS TESTS -------------------------------------- //

// ---- True component ---- //
Test(true_component_tests, initialization_of_true) {
    nts::TrueComponnet trueComponent;
    auto pins = trueComponent.getPins();
    cr_assert_eq(*pins[1].first, nts::Tristate::True, "The TrueComponent's output pin should be initialized to Tristate::True");
    cr_assert_eq(pins[1].second, nts::OUTPUT, "The TrueComponent's pin should be set as OUTPUT");
}

Test(true_component_tests, simulate_no_effect_of_true) {
    nts::TrueComponnet trueComponent;
    auto initialPinState = *trueComponent.getPins()[1].first;
    trueComponent.simulate(0);
    auto postSimulatePinState = *trueComponent.getPins()[1].first;
    cr_assert_eq(initialPinState, postSimulatePinState, "Simulate method should not alter the TrueComponent's state");
}

// ---- False component ---- //
Test(false_component_tests, initialization_of_false) {
    nts::FalseComponent falseComponent;
    auto pins = falseComponent.getPins();
    cr_assert_eq(*pins[1].first, nts::Tristate::False, "The FalseComponent's output pin should be initialized to Tristate::False");
    cr_assert_eq(pins[1].second, nts::OUTPUT, "The FalseComponent's pin should be set as OUTPUT");
}

Test(false_component_tests, simulate_no_effect_of_false) {
    nts::FalseComponent falseComponent;
    auto initialPinState = *falseComponent.getPins()[1].first;
    falseComponent.simulate(0);
    auto postSimulatePinState = *falseComponent.getPins()[1].first;
    cr_assert_eq(initialPinState, postSimulatePinState, "Simulate method should not alter the FalseComponent's state");
}

// ---- Clock component ---- //
Test(clock_component_tests, initialization_of_clock) {
    nts::ClockComponent clockComponent;
    auto pins = clockComponent.getPins();
    cr_assert_eq(*pins[1].first, nts::Tristate::Undefined, "ClockComponent should initialize with an Undefined state");
    cr_assert_eq(pins[1].second, nts::OUTPUT, "ClockComponent's pin should be set as OUTPUT");
}

// Test the simulate method toggles the state correctly
Test(clock_component_tests, simulate_toggle) {
    nts::ClockComponent clockComponent;

    clockComponent.simulate(0);
    auto stateAfterFirstTick = *clockComponent.getPins()[1].first;
    cr_assert_eq(stateAfterFirstTick, nts::Tristate::Undefined, "First simulate call should not change the Undefined state");

    clockComponent.setInput(nts::Tristate::True);
    clockComponent.simulate(1);
    clockComponent.simulate(2);
    auto stateAfterToggle = *clockComponent.getPins()[1].first;
    cr_assert_eq(stateAfterToggle, nts::Tristate::False, "ClockComponent should toggle state to False");
}

// Test setInput method sets the state correctly and makes it unavailable for the next tick
Test(clock_component_tests, set_input_of_clock) {
    nts::ClockComponent clockComponent;
    clockComponent.setInput(nts::Tristate::True);
    auto stateAfterSetInput = *clockComponent.getPins()[1].first;
    cr_assert_eq(stateAfterSetInput, nts::Tristate::True, "setInput should set the state to True");

    clockComponent.simulate(0);
    auto stateAfterSimulate = *clockComponent.getPins()[1].first;
    cr_assert_eq(stateAfterSimulate, nts::Tristate::True, "State should remain True after simulate due to _availableTick being false");
}

// ---- Input component ---- //

Test(input_component_tests, initialization_of_input) {
    nts::InputComponent inputComponent;
    auto pins = inputComponent.getPins();
    cr_assert_eq(*pins[1].first, nts::Tristate::Undefined, "InputComponent should initialize with an Undefined state");
}

// Test the setInput method updates the state correctly
Test(input_component_tests, set_input_of_input) {
    nts::InputComponent inputComponent;
    inputComponent.setInput(nts::Tristate::True);
    auto stateAfterSetInputTrue = *inputComponent.getPins()[1].first;
    cr_assert_eq(stateAfterSetInputTrue, nts::Tristate::True, "setInput should update the state to True");

    inputComponent.setInput(nts::Tristate::False);
    auto stateAfterSetInputFalse = *inputComponent.getPins()[1].first;
    cr_assert_eq(stateAfterSetInputFalse, nts::Tristate::False, "setInput should update the state to False");
}

Test(input_component_tests, simulate_no_effect_of_clock) {
    nts::InputComponent inputComponent;
    inputComponent.setInput(nts::Tristate::True);
    inputComponent.simulate(0);
    auto stateAfterSimulate = *inputComponent.getPins()[1].first;
    cr_assert_eq(stateAfterSimulate, nts::Tristate::True, "Simulate method should not alter the InputComponent's state");
}

// ---- Output component ---- //

Test(output_component_tests, initialization_of_output) {
    nts::OutputComponent outputComponent;
    auto pins = outputComponent.getPins();
    cr_assert_eq(*pins[1].first, nts::Tristate::Undefined, "OutputComponent should initialize with an Undefined state");
    cr_assert_eq(pins[1].second, nts::INPUT, "OutputComponent's pin should be set as INPUT");
}

Test(output_component_tests, simulate_no_effect_of_output) {
    nts::OutputComponent outputComponent;
    *outputComponent.getPins()[1].first = nts::Tristate::True;
    outputComponent.simulate(0);
    auto stateAfterSimulate = *outputComponent.getPins()[1].first;
    cr_assert_eq(stateAfterSimulate, nts::Tristate::True, "Simulate method should not alter the OutputComponent's state");
}


// -------------------------------------- ELEMENTARY COMPONENTS TESTS -------------------------------------- //

// ---- And component ---- //

Test(and_component_tests, initialization_of_and) {
    nts::AndComponent andComponent;
    auto pins = andComponent.getPins();
    cr_assert_eq(*pins[1].first, nts::Tristate::Undefined, "Input pin 1 should initialize as Undefined");
    cr_assert_eq(*pins[2].first, nts::Tristate::Undefined, "Input pin 2 should initialize as Undefined");
    cr_assert_eq(*pins[3].first, nts::Tristate::Undefined, "Output pin should initialize as Undefined");
}

// Test AND logic: True AND True = True
Test(and_component_tests, true_and_true_and) {
    nts::TrueComponnet trueComponent1;
    nts::TrueComponnet trueComponent2;
    nts::AndComponent andComponent;
    andComponent.setLink(1, trueComponent1, 1);
    andComponent.setLink(2, trueComponent2, 1);
    andComponent.simulate(0);
    auto output = andComponent.compute(3);
    cr_assert_eq(output, nts::Tristate::True, "True AND True should be True");
}

// Test AND logic: False AND True = False
Test(and_component_tests, false_and_true_and) {
    nts::TrueComponnet trueComponent;
    nts::FalseComponent falseComponent;

    nts::AndComponent andComponent;
    andComponent.setLink(1, trueComponent, 1);
    andComponent.setLink(2, falseComponent, 1);
    andComponent.simulate(0);
    auto output = andComponent.compute(3);
    cr_assert_eq(output, nts::Tristate::False, "False AND True should be False");
}

// Test AND logic: False AND False = False
Test(and_component_tests, false_and_false_and) {
    nts::FalseComponent falseComponent1;
    nts::FalseComponent falseComponent2;
    nts::AndComponent andComponent;
    andComponent.setLink(1, falseComponent1, 1);
    andComponent.setLink(2, falseComponent2, 1);
    andComponent.simulate(0);
    auto output = andComponent.compute(3);
    cr_assert_eq(output, nts::Tristate::False, "False AND False should be False");
}

// Test AND logic: Undefined AND True/False = Undefined
Test(and_component_tests, undefined_and_any_and) {
    nts::TrueComponnet trueComponent;
    nts::FalseComponent falseComponent;
    nts::InputComponent inputComponent;
    nts::AndComponent andComponent;
    andComponent.setLink(1, inputComponent, 1);
    andComponent.setLink(2, trueComponent, 1);
    andComponent.simulate(0);
    auto outputTrue = andComponent.compute(3);
    cr_assert_eq(outputTrue, nts::Tristate::Undefined, "Undefined AND True should be Undefined");

    andComponent.setLink(2, falseComponent, 1);
    andComponent.simulate(1);
    auto outputFalse = andComponent.compute(3);
    cr_assert_eq(outputFalse, nts::Tristate::False, "Undefined AND False should be False");
}


// ---- Or component ---- //

Test(or_component_tests, initialization_of_or) {
    nts::OrComponent orComponent;
    auto pins = orComponent.getPins();
    cr_assert_eq(*pins[1].first, nts::Tristate::Undefined, "Input pin 1 should initialize as Undefined");
    cr_assert_eq(*pins[2].first, nts::Tristate::Undefined, "Input pin 2 should initialize as Undefined");
    cr_assert_eq(*pins[3].first, nts::Tristate::Undefined, "Output pin should initialize as Undefined");
}

// Test AND logic: True AND True = True
Test(or_component_tests, true_and_true_or) {
    nts::TrueComponnet trueComponent1;
    nts::TrueComponnet trueComponent2;
    nts::OrComponent orComponent;
    orComponent.setLink(1, trueComponent1, 1);
    orComponent.setLink(2, trueComponent2, 1);
    orComponent.simulate(0);
    auto output = orComponent.compute(3);
    cr_assert_eq(output, nts::Tristate::True, "True AND True should be True");
}

// Test AND logic: False AND True = True
Test(or_component_tests, false_and_true_or) {
    nts::TrueComponnet trueComponent;
    nts::FalseComponent falseComponent;

    nts::OrComponent orComponent;
    orComponent.setLink(1, trueComponent, 1);
    orComponent.setLink(2, falseComponent, 1);
    orComponent.simulate(0);
    auto output = orComponent.compute(3);
    cr_assert_eq(output, nts::Tristate::True, "False AND True should be True");
}

// Test AND logic: False AND False = False
Test(or_component_tests, false_and_false_or) {
    nts::FalseComponent falseComponent1;
    nts::FalseComponent falseComponent2;
    nts::OrComponent orComponent;
    orComponent.setLink(1, falseComponent1, 1);
    orComponent.setLink(2, falseComponent2, 1);
    orComponent.simulate(0);
    auto output = orComponent.compute(3);
    cr_assert_eq(output, nts::Tristate::False, "False AND False should be False");
}

// Test AND logic: Undefined AND True/False = Undefined
Test(or_component_tests, undefined_and_any_or) {
    nts::TrueComponnet trueComponent;
    nts::FalseComponent falseComponent;
    nts::InputComponent inputComponent;
    nts::OrComponent orComponent;
    orComponent.setLink(1, inputComponent, 1);
    orComponent.setLink(2, trueComponent, 1);
    orComponent.simulate(0);
    auto outputTrue = orComponent.compute(3);
    cr_assert_eq(outputTrue, nts::Tristate::True, "Undefined AND True should be True");

    orComponent.setLink(2, falseComponent, 1);
    orComponent.simulate(1);
    auto outputFalse = orComponent.compute(3);
    cr_assert_eq(outputFalse, nts::Tristate::Undefined, "Undefined AND False should be Undefined");
}

// ---- Nand component ---- //


Test(nand_component_tests, initialization_of_nand) {
    nts::NandComponent nandComponent;
    auto pins = nandComponent.getPins();
    cr_assert_eq(*pins[1].first, nts::Tristate::Undefined, "Input pin 1 should initialize as Undefined");
    cr_assert_eq(*pins[2].first, nts::Tristate::Undefined, "Input pin 2 should initialize as Undefined");
    cr_assert_eq(*pins[3].first, nts::Tristate::Undefined, "Output pin should initialize as Undefined");
}

// Test AND logic: True AND True = False
Test(nand_component_tests, true_and_true_nand) {
    nts::TrueComponnet trueComponent1;
    nts::TrueComponnet trueComponent2;
    nts::NandComponent nandComponent;
    nandComponent.setLink(1, trueComponent1, 1);
    nandComponent.setLink(2, trueComponent2, 1);
    nandComponent.simulate(0);
    auto output = nandComponent.compute(3);
    cr_assert_eq(output, nts::Tristate::False, "True AND True should be False");
}

// Test AND logic: False AND True = True
Test(nand_component_tests, false_and_true_nand) {
    nts::TrueComponnet trueComponent;
    nts::FalseComponent falseComponent;

    nts::NandComponent nandComponent;
    nandComponent.setLink(1, trueComponent, 1);
    nandComponent.setLink(2, falseComponent, 1);
    nandComponent.simulate(0);
    auto output = nandComponent.compute(3);
    cr_assert_eq(output, nts::Tristate::True, "False AND True should be True");
}

// Test AND logic: False AND False = False
Test(nand_component_tests, false_and_false_nand) {
    nts::FalseComponent falseComponent1;
    nts::FalseComponent falseComponent2;
    nts::NandComponent nandComponent;
    nandComponent.setLink(1, falseComponent1, 1);
    nandComponent.setLink(2, falseComponent2, 1);
    nandComponent.simulate(0);
    auto output = nandComponent.compute(3);
    cr_assert_eq(output, nts::Tristate::True, "False AND False should be True");
}

// Test AND logic: Undefined AND True/False = Undefined
Test(nand_component_tests, undefined_and_any_nand) {
    nts::TrueComponnet trueComponent;
    nts::FalseComponent falseComponent;
    nts::InputComponent inputComponent;
    nts::NandComponent nandComponent;
    nandComponent.setLink(1, inputComponent, 1);
    nandComponent.setLink(2, trueComponent, 1);
    nandComponent.simulate(0);
    auto outputTrue = nandComponent.compute(3);
    cr_assert_eq(outputTrue, nts::Tristate::Undefined, "Undefined AND True should be True");

    nandComponent.setLink(2, falseComponent, 1);
    nandComponent.simulate(1);
    auto outputFalse = nandComponent.compute(3);
    cr_assert_eq(outputFalse, nts::Tristate::True, "Undefined AND False should be True");
}

// ---- Nor component ---- //

Test(nor_component_tests, initialization_of_nor) {
    nts::NorComponent norComponent;
    auto pins = norComponent.getPins();
    cr_assert_eq(*pins[1].first, nts::Tristate::Undefined, "Input pin 1 should initialize as Undefined");
    cr_assert_eq(*pins[2].first, nts::Tristate::Undefined, "Input pin 2 should initialize as Undefined");
    cr_assert_eq(*pins[3].first, nts::Tristate::Undefined, "Output pin should initialize as Undefined");
}

// Test AND logic: True AND True = False
Test(nor_component_tests, true_and_true_nor) {
    nts::TrueComponnet trueComponent1;
    nts::TrueComponnet trueComponent2;
    nts::NorComponent norComponent;
    norComponent.setLink(1, trueComponent1, 1);
    norComponent.setLink(2, trueComponent2, 1);
    norComponent.simulate(0);
    auto output = norComponent.compute(3);
    cr_assert_eq(output, nts::Tristate::False, "True AND True should be False");
}

// Test AND logic: False AND True = False
Test(nor_component_tests, false_and_true_nor) {
    nts::TrueComponnet trueComponent;
    nts::FalseComponent falseComponent;

    nts::NorComponent norComponent;
    norComponent.setLink(1, trueComponent, 1);
    norComponent.setLink(2, falseComponent, 1);
    norComponent.simulate(0);
    auto output = norComponent.compute(3);
    cr_assert_eq(output, nts::Tristate::False, "False AND True should be False");
}

// Test AND logic: False AND False = True
Test(nor_component_tests, false_and_false_or) {
    nts::FalseComponent falseComponent1;
    nts::FalseComponent falseComponent2;
    nts::NorComponent norComponent;
    norComponent.setLink(1, falseComponent1, 1);
    norComponent.setLink(2, falseComponent2, 1);
    norComponent.simulate(0);
    auto output = norComponent.compute(3);
    cr_assert_eq(output, nts::Tristate::True, "False AND False should be true");
}

// Test AND logic: Undefined AND True/False = Undefined
Test(nor_component_tests, undefined_and_any_or) {
    nts::TrueComponnet trueComponent;
    nts::FalseComponent falseComponent;
    nts::InputComponent inputComponent;
    nts::NorComponent norComponent;
    norComponent.setLink(1, inputComponent, 1);
    norComponent.setLink(2, trueComponent, 1);
    norComponent.simulate(0);
    auto outputTrue = norComponent.compute(3);
    cr_assert_eq(outputTrue, nts::Tristate::False, "Undefined AND True should be False");

    norComponent.setLink(2, falseComponent, 1);
    norComponent.simulate(1);
    auto outputFalse = norComponent.compute(3);
    cr_assert_eq(outputFalse, nts::Tristate::Undefined, "Undefined AND False should be Undefined");
}