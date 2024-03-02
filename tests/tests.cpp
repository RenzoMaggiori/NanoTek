#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/logging.h>
#include "Parser.hpp"
#include "Factory.hpp"
#include "Circuit.hpp"
#include "SelectorComponent.hpp"
#include "JohnsonComponent.hpp"
#include "FlipflopComponent.hpp"
#include "AdderComponent.hpp"

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
    std::vector<std::string> knownTypes = {"4001", "4008", "4011", "4013", "4017", "4030", "4040", "4069", "4071", "4081", "4512", "4801", "2716", "input", "output", "true", "false", "clock", "or", "nor", "xor", "not", "and", "nand"};
    for (const auto& type : knownTypes) {
        cr_assert_no_throw(factory.createComponent(type), nts::Error, "Factory should successfully create component of type: %s", type.c_str());
    }
}

// -------------------------------------- ACOMPONENT TESTS -------------------------------------- //

Test(acomponent_tests, function_calls) {
    nts::TrueComponnet trueComponent;
    auto pins = trueComponent.getPins();
    auto type = trueComponent.getPinType(1);
    bool status = trueComponent.setInput(nts::Tristate::True);
    auto links = trueComponent.getOutputLink();
    trueComponent.setPriority(1);
    std::size_t priority = trueComponent.getPriority();
    cr_assert_eq(*pins[1].first, nts::Tristate::True, "The TrueComponent's output pin should be initialized to Tristate::True");
    cr_assert_eq(pins[1].second, nts::OUTPUT, "The TrueComponent's pin should be set as OUTPUT");
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

Test(output_component_tests, true_output) {
    nts::TrueComponnet trueComponent;
    nts::OutputComponent outputComponent;
    outputComponent.setLink(1, trueComponent, 1);
    outputComponent.simulate(0);
    auto stateAfterSimulate = outputComponent.compute(1);
    cr_assert_eq(stateAfterSimulate, nts::Tristate::True, "Output should be true");
}

Test(output_component, set_input_without_hybrid_pin_type) {
    nts::OutputComponent outputComponent;
    bool result = outputComponent.setInput(nts::Tristate::True);
    cr_expect_eq(result, false, "setInput returned false when pin type wasn't HYBRID.");
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
Test(nor_component_tests, false_and_false_nor) {
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
Test(nor_component_tests, undefined_and_any_nor) {
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

// ---- Xor component ---- //

Test(xor_component_tests, initialization_of_xor) {
    nts::XorComponent xorComponent;
    auto pins = xorComponent.getPins();
    cr_assert_eq(*pins[1].first, nts::Tristate::Undefined, "Input pin 1 should initialize as Undefined");
    cr_assert_eq(*pins[2].first, nts::Tristate::Undefined, "Input pin 2 should initialize as Undefined");
    cr_assert_eq(*pins[3].first, nts::Tristate::Undefined, "Output pin should initialize as Undefined");
}

// Test AND logic: True AND True = False
Test(xor_component_tests, true_and_true_xor) {
    nts::TrueComponnet trueComponent1;
    nts::TrueComponnet trueComponent2;
    nts::XorComponent xorComponent;
    xorComponent.setLink(1, trueComponent1, 1);
    xorComponent.setLink(2, trueComponent2, 1);
    xorComponent.simulate(0);
    auto output = xorComponent.compute(3);
    cr_assert_eq(output, nts::Tristate::False, "True AND True should be False");
}

// Test AND logic: False AND True = True
Test(xor_component_tests, false_and_true_xor) {
    nts::TrueComponnet trueComponent;
    nts::FalseComponent falseComponent;

    nts::XorComponent xorComponent;
    xorComponent.setLink(1, trueComponent, 1);
    xorComponent.setLink(2, falseComponent, 1);
    xorComponent.simulate(0);
    auto output = xorComponent.compute(3);
    cr_assert_eq(output, nts::Tristate::True, "False AND True should be True");
}

// Test AND logic: False AND False = False
Test(xor_component_tests, false_and_false_xor) {
    nts::FalseComponent falseComponent1;
    nts::FalseComponent falseComponent2;
    nts::XorComponent xorComponent;
    xorComponent.setLink(1, falseComponent1, 1);
    xorComponent.setLink(2, falseComponent2, 1);
    xorComponent.simulate(0);
    auto output = xorComponent.compute(3);
    cr_assert_eq(output, nts::Tristate::False, "False AND False should be False");
}

// Test AND logic: Undefined AND True/False = Undefined
Test(xor_component_tests, undefined_and_any_xor) {
    nts::TrueComponnet trueComponent;
    nts::FalseComponent falseComponent;
    nts::InputComponent inputComponent;
    nts::XorComponent xorComponent;
    xorComponent.setLink(1, inputComponent, 1);
    xorComponent.setLink(2, trueComponent, 1);
    xorComponent.simulate(0);
    auto outputTrue = xorComponent.compute(3);
    cr_assert_eq(outputTrue, nts::Tristate::Undefined, "Undefined AND True should be Undefined");

    xorComponent.setLink(2, falseComponent, 1);
    xorComponent.simulate(1);
    auto outputFalse = xorComponent.compute(3);
    cr_assert_eq(outputFalse, nts::Tristate::Undefined, "Undefined AND False should be Undefined");
}

// ---- Not component ---- //

Test(not_component_tests, initialization_of_not) {
    nts::NotComponent notComponent;
    auto pins = notComponent.getPins();
    cr_assert_eq(*pins[1].first, nts::Tristate::Undefined, "Input pin 1 should initialize as Undefined");
    cr_assert_eq(*pins[2].first, nts::Tristate::Undefined, "Input pin 2 should initialize as Undefined");
}

// Test logic: True = False
Test(not_component_tests, true_not) {
    nts::TrueComponnet trueComponent;
    nts::NotComponent notComponent;
    notComponent.setLink(1, trueComponent, 1);
    notComponent.simulate(0);
    auto output = notComponent.compute(2);
    cr_assert_eq(output, nts::Tristate::False, "True should be False");
}

// Test logic: False = True
Test(not_component_tests, false_not) {
    nts::FalseComponent falseComponent;
    nts::NotComponent notComponent;
    notComponent.setLink(1, falseComponent, 1);
    notComponent.simulate(0);
    auto output = notComponent.compute(2);
    cr_assert_eq(output, nts::Tristate::True, "False should be True");
}

// Test logic: Undefined = Undefined
Test(not_component_tests, undifined_not) {
    nts::InputComponent inputCOmponent;
    nts::NotComponent notComponent;
    notComponent.setLink(1, inputCOmponent, 1);
    notComponent.simulate(0);
    auto output = notComponent.compute(2);
    cr_assert_eq(output, nts::Tristate::Undefined, "Undefined should be Undefined");
}


// ---- Selector component ---- //

Test(selector_component_tests, initialization) {
    nts::SelectorComponent selectorComponent;
    auto pins = selectorComponent.getPins();
    for (std::size_t i = 1; i < 16; i++)
        cr_assert_eq(*pins[i].first, nts::Tristate::Undefined, "Input pin should initialize as Undefined");
}

Test(selector_component_tests, out_0) {
    nts::InputComponent inputComponent;
    nts::TrueComponnet trueComponent;
    nts::TrueComponnet trueComponent1;
    nts::TrueComponnet trueComponent2;
    nts::TrueComponnet trueComponent3;
    nts::FalseComponent falseComponent1;
    nts::FalseComponent falseComponent2;
    nts::FalseComponent falseComponent3;
    nts::FalseComponent falseComponent4;
    nts::FalseComponent falseComponent5;
    nts::SelectorComponent selectorComponent;
    selectorComponent.setLink(10, falseComponent1, 1);
    selectorComponent.setLink(15, falseComponent2, 1);
    selectorComponent.setLink(11, falseComponent3, 1);
    selectorComponent.setLink(12, falseComponent4, 1);
    selectorComponent.setLink(13, falseComponent5, 1);
    selectorComponent.setLink(1, trueComponent, 1);
    selectorComponent.simulate(0);
    auto output = selectorComponent.compute(14);
    cr_assert_eq(output, nts::Tristate::True, "Selector out should be True");
    selectorComponent.setLink(11, trueComponent1, 1);
    selectorComponent.simulate(0);
    output = selectorComponent.compute(14);
    cr_assert_eq(output, nts::Tristate::Undefined, "Selector out should be Undefined");
    selectorComponent.setLink(12, trueComponent2, 1);
    selectorComponent.simulate(0);
    output = selectorComponent.compute(14);
    cr_assert_eq(output, nts::Tristate::Undefined, "Selector out should be Undefined");
    selectorComponent.setLink(13, trueComponent3, 1);
    selectorComponent.simulate(0);
    output = selectorComponent.compute(14);
    cr_assert_eq(output, nts::Tristate::Undefined, "Selector out should be Undefined");
    selectorComponent.setLink(11, falseComponent3, 1);
    selectorComponent.simulate(0);
    output = selectorComponent.compute(14);
    cr_assert_eq(output, nts::Tristate::Undefined, "Selector out should be Undefined");
    selectorComponent.setLink(12, falseComponent4, 1);
    selectorComponent.simulate(0);
    output = selectorComponent.compute(14);
    cr_assert_eq(output, nts::Tristate::Undefined, "Selector out should be Undefined");
    selectorComponent.setLink(12, inputComponent, 1);
    selectorComponent.simulate(0);
    output = selectorComponent.compute(14);
    cr_assert_eq(output, nts::Tristate::Undefined, "Selector out should be Undefined");
    selectorComponent.setLink(12, falseComponent4, 1);
    selectorComponent.setLink(11, trueComponent2, 1);
    selectorComponent.simulate(0);
    output = selectorComponent.compute(14);
    cr_assert_eq(output, nts::Tristate::Undefined, "Selector out should be Undefined");
    selectorComponent.setLink(13, falseComponent4, 1);
    selectorComponent.setLink(12, trueComponent2, 1);
    selectorComponent.setLink(11, falseComponent3, 1);
    selectorComponent.simulate(0);
    output = selectorComponent.compute(14);
    cr_assert_eq(output, nts::Tristate::Undefined, "Selector out should be Undefined");
}

Test(selector_component_tests, inhibit) {
    nts::TrueComponnet trueComponent;
    nts::FalseComponent falseComponent;
    nts::SelectorComponent selectorComponent;
    selectorComponent.setLink(10, trueComponent, 1);
    selectorComponent.setLink(15, falseComponent, 1);
    selectorComponent.simulate(0);
    auto output = selectorComponent.compute(14);
    cr_assert_eq(output, nts::Tristate::False, "Selector out should be False");
}

Test(selector_component_tests, enable) {
    nts::TrueComponnet trueComponent;
    nts::FalseComponent falseComponent;
    nts::SelectorComponent selectorComponent;
    selectorComponent.setLink(10, falseComponent, 1);
    selectorComponent.setLink(15, trueComponent, 1);
    selectorComponent.simulate(0);
    auto output = selectorComponent.compute(14);
    cr_assert_eq(output, nts::Tristate::Undefined, "Selector out should be Undefined");
}


// ---- Adder component ---- //

Test(adder_component_tests, initialization) {
    nts::AdderComponent adderComponent;
    auto pins = adderComponent.getPins();
    for (std::size_t i = 1; i < 6; i++)
        cr_assert_eq(*pins[i].first, nts::Tristate::Undefined, "Input pin should initialize as Undefined");
}

Test(adder_component_tests, out_0) {
    nts::InputComponent inputComponent;
    nts::TrueComponnet trueComponent;
    nts::TrueComponnet trueComponent1;
    nts::TrueComponnet trueComponent2;
    nts::TrueComponnet trueComponent3;
    nts::FalseComponent falseComponent1;
    nts::FalseComponent falseComponent2;
    nts::FalseComponent falseComponent3;
    nts::FalseComponent falseComponent4;
    nts::FalseComponent falseComponent5;
    nts::AdderComponent adderComponent;
    adderComponent.setLink(1, falseComponent1, 1);
    adderComponent.setLink(2, falseComponent2, 1);
    adderComponent.setLink(3, falseComponent3, 1);
    adderComponent.simulate(0);
    auto output1 = adderComponent.compute(4);
    auto output2 = adderComponent.compute(5);
    cr_assert_eq(output1, nts::Tristate::False, "Adder carry out should be False");
    cr_assert_eq(output2, nts::Tristate::False, "Adder sum should be False");
    adderComponent.setLink(2, trueComponent, 1);
    adderComponent.simulate(0);
    output1 = adderComponent.compute(4);
    output2 = adderComponent.compute(5);
    cr_assert_eq(output1, nts::Tristate::False, "Adder carry out should be False");
    cr_assert_eq(output2, nts::Tristate::True, "Adder sum should be True");
    adderComponent.setLink(2, falseComponent2, 1);
    adderComponent.setLink(3, trueComponent, 1);
    adderComponent.simulate(0);
    output1 = adderComponent.compute(4);
    output2 = adderComponent.compute(5);
    cr_assert_eq(output1, nts::Tristate::False, "Adder carry out should be False");
    cr_assert_eq(output2, nts::Tristate::True, "Adder sum should be True");
    adderComponent.setLink(2, trueComponent1, 1);
    adderComponent.setLink(3, trueComponent, 1);
    adderComponent.simulate(0);
    output1 = adderComponent.compute(4);
    output2 = adderComponent.compute(5);
    cr_assert_eq(output1, nts::Tristate::True, "Adder carry out should be True");
    cr_assert_eq(output2, nts::Tristate::False, "Adder sum should be False");
    adderComponent.setLink(1, trueComponent1, 1);
    adderComponent.setLink(2, falseComponent2, 1);
    adderComponent.setLink(3, falseComponent1, 1);
    adderComponent.simulate(0);
    output1 = adderComponent.compute(4);
    output2 = adderComponent.compute(5);
    cr_assert_eq(output1, nts::Tristate::False, "Adder carry out should be False");
    cr_assert_eq(output2, nts::Tristate::True, "Adder sum should be True");
    adderComponent.setLink(2, trueComponent, 1);
    adderComponent.simulate(0);
    output1 = adderComponent.compute(4);
    output2 = adderComponent.compute(5);
    cr_assert_eq(output1, nts::Tristate::True, "Adder carry out should be True");
    cr_assert_eq(output2, nts::Tristate::False, "Adder sum should be False");
    adderComponent.setLink(2, falseComponent2, 1);
    adderComponent.setLink(3, trueComponent, 1);
    adderComponent.simulate(0);
    output1 = adderComponent.compute(4);
    output2 = adderComponent.compute(5);
    cr_assert_eq(output1, nts::Tristate::True, "Adder carry out should be True");
    cr_assert_eq(output2, nts::Tristate::False, "Adder sum should be False");
    adderComponent.setLink(2, trueComponent2, 1);
    adderComponent.simulate(0);
    output1 = adderComponent.compute(4);
    output2 = adderComponent.compute(5);
    cr_assert_eq(output1, nts::Tristate::True, "Adder carry out should be True");
    cr_assert_eq(output2, nts::Tristate::True, "Adder sum should be True");
    adderComponent.setLink(2, inputComponent, 1);
    adderComponent.simulate(0);
    output1 = adderComponent.compute(4);
    output2 = adderComponent.compute(5);
    cr_assert_eq(output1, nts::Tristate::Undefined, "Adder carry out should be Undefined");
    cr_assert_eq(output2, nts::Tristate::Undefined, "Adder sum should be Undefined");
}


// ---- Flip-Flop component ---- //

Test(flipflop_component_tests, initialization) {
    nts::FlipflopComponent flipflopComponent;
    auto pins = flipflopComponent.getPins();
    for (std::size_t i = 1; i < 7; i++)
        cr_assert_eq(*pins[i].first, nts::Tristate::Undefined, "Input pin should initialize as Undefined");
}

Test(flipflop_component_tests, outputs) {
    nts::TrueComponnet trueComponent;
    nts::TrueComponnet trueComponent1;
    nts::TrueComponnet trueComponent2;
    nts::TrueComponnet trueComponent3;
    nts::FalseComponent falseComponent1;
    nts::FalseComponent falseComponent2;
    nts::FalseComponent falseComponent3;
    nts::FlipflopComponent flipflopComponent;
    flipflopComponent.setLink(3, trueComponent, 1);
    flipflopComponent.setLink(4, falseComponent1, 1);
    flipflopComponent.simulate(0);
    auto output1 = flipflopComponent.compute(5);
    auto output2 = flipflopComponent.compute(6);
    cr_assert_eq(output1, nts::Tristate::True, "q carry out should be True");
    cr_assert_eq(output2, nts::Tristate::False, "q' sum should be False");
    flipflopComponent.setLink(4, trueComponent1, 1);
    flipflopComponent.simulate(0);
    output1 = flipflopComponent.compute(5);
    output2 = flipflopComponent.compute(6);
    cr_assert_eq(output1, nts::Tristate::True, "q carry out should be True");
    cr_assert_eq(output2, nts::Tristate::True, "q' sum should be True");
    flipflopComponent.setLink(3, falseComponent1, 1);
    flipflopComponent.simulate(0);
    output1 = flipflopComponent.compute(5);
    output2 = flipflopComponent.compute(6);
    cr_assert_eq(output1, nts::Tristate::False, "q carry out should be False");
    cr_assert_eq(output2, nts::Tristate::True, "q' sum should be True");
    flipflopComponent.setLink(2, trueComponent, 1);
    flipflopComponent.setLink(1, trueComponent2, 1);
    flipflopComponent.simulate(0);
    output1 = flipflopComponent.compute(5);
    output2 = flipflopComponent.compute(6);
    cr_assert_eq(output1, nts::Tristate::False, "q carry out should be False");
    cr_assert_eq(output2, nts::Tristate::True, "q' sum should be True");
    flipflopComponent.setLink(1, falseComponent3, 1);
    flipflopComponent.simulate(0);
    output1 = flipflopComponent.compute(5);
    output2 = flipflopComponent.compute(6);
    cr_assert_eq(output1, nts::Tristate::False, "q carry out should be False");
    cr_assert_eq(output2, nts::Tristate::True, "q' sum should be True");
}

// ---- Counter component ---- //
Test(counter_component_tests, initialization) {
    nts::CounterComponent counterComponent;
    auto pins = counterComponent.getPins();
    for (std::size_t i = 1; i < 17; i++)
        cr_assert_eq(*pins[i].first, nts::Tristate::Undefined, "Input pin should initialize as Undefined");
}

Test(counter_component_tests, outputs) {
    nts::TrueComponnet trueComponent;
    nts::TrueComponnet trueComponent1;
    nts::FalseComponent falseComponent1;
    nts::FalseComponent falseComponent2;
    nts::CounterComponent counterComponent;
    counterComponent.setLink(11, falseComponent1, 1);
    counterComponent.simulate(0);
    auto output1 = counterComponent.compute(1);
    cr_assert_eq(output1, nts::Tristate::False, "out_1 carry out should be False");
    counterComponent.setLink(11, trueComponent, 1);
    counterComponent.setLink(10, falseComponent1, 1);
    counterComponent.simulate(0);
    counterComponent.setLink(10, trueComponent1, 1);
    counterComponent.simulate(0);
    output1 = counterComponent.compute(1);
    cr_assert_eq(output1, nts::Tristate::False, "out_1 carry out should be False");
    counterComponent.simulate(0);
    output1 = counterComponent.compute(1);
    cr_assert_eq(output1, nts::Tristate::False, "out_1 carry out should be False");

}

// ---- Johnson component ---- //

Test(johnson_component_tests, outputs) {
    nts::TrueComponnet trueComponent;
    nts::TrueComponnet trueComponent1;
    nts::FalseComponent falseComponent1;
    nts::FalseComponent falseComponent2;
    nts::JohnsonComponent johnsonComponent;
    johnsonComponent.setLink(3, trueComponent, 1);
    johnsonComponent.simulate(0);
    auto output1 = johnsonComponent.compute(4);
    cr_assert_eq(output1, nts::Tristate::False, "out_1 should be False");
    johnsonComponent.setLink(3, falseComponent2, 1);
    johnsonComponent.setLink(1, falseComponent1, 1);
    johnsonComponent.simulate(0);
    johnsonComponent.setLink(1, trueComponent1, 1);
    johnsonComponent.simulate(0);
    johnsonComponent.setLink(1, falseComponent1, 1);
    johnsonComponent.simulate(0);
    johnsonComponent.setLink(1, trueComponent1, 1);
    johnsonComponent.simulate(0);
    output1 = johnsonComponent.compute(5);
    cr_assert_eq(output1, nts::Tristate::True, "out_1 should be True");
    for (std::size_t i = 0; i < 8; i++) {
        johnsonComponent.setLink(1, falseComponent1, 1);
        johnsonComponent.simulate(0);
        johnsonComponent.setLink(1, trueComponent1, 1);
        johnsonComponent.simulate(0);
    }
    output1 = johnsonComponent.compute(13);
    cr_assert_eq(output1, nts::Tristate::False, "out_s should be True");
    johnsonComponent.setLink(1, falseComponent1, 1);
    johnsonComponent.simulate(0);
    johnsonComponent.setLink(1, trueComponent1, 1);
    johnsonComponent.simulate(0);
    output1 = johnsonComponent.compute(4);
    cr_assert_eq(output1, nts::Tristate::True, "out_s should be False");
}

// ---- Logger component ---- //
Test(logger_component_tests, initialization) {
    nts::LoggerComponent loggerComponent;
    auto pins = loggerComponent.getPins();
    for (std::size_t i = 1; i < 11; i++)
        cr_assert_eq(*pins[i].first, nts::Tristate::Undefined, "Input pin should initialize as Undefined");
}

Test(logger_component_tests, inputs) {
    nts::TrueComponnet trueComponent;
    nts::TrueComponnet trueComponent1;
    nts::FalseComponent falseComponent;
    nts::FalseComponent falseComponent1;
    nts::LoggerComponent loggerComponent;
    loggerComponent.setLink(9, falseComponent, 1);
    loggerComponent.setLink(10, falseComponent, 1);
    loggerComponent.simulate(0);
    loggerComponent.setLink(9, trueComponent, 1);
    loggerComponent.setLink(1, trueComponent1, 1);
    loggerComponent.simulate(0);
    auto output1 = loggerComponent.compute(1);
    cr_assert_eq(output1, nts::Tristate::True, "in_1 carry out should be True");
}

// -------------------------------------- CIRCUITS TESTS -------------------------------------- //

Test(circuit_test, add_and_use_true) {
    nts::Circuit circuit;
    auto trueComponent = std::make_unique<nts::TrueComponnet>();

    circuit.addComponent("true1", std::move(trueComponent));
    auto& components = circuit.getComponents();

    cr_assert_eq(components.size(), 1, "Expected components size to be 1.");
    cr_assert(components.find("true1") != components.end(), "Component 'true1' not found.");
}

Test(circuit, display_with_true_component, .init=cr_redirect_stdout) {
    nts::Circuit circuit;
    auto trueComponent = std::make_unique<nts::TrueComponnet>();

    circuit.addComponent("true1", std::move(trueComponent));
    circuit.display();

    // Adjust the expected string according to your display format.
    cr_assert_stdout_eq_str("tick: 0\ninput(s):\noutput(s):\n", "The display output did not match the expected output for TrueComponent.");
}


