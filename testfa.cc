#include "gtest/gtest.h"

#include "Automaton.h"

#include <iostream>

// --- TEST AutomatonIsValid ---

TEST(AutomatonIsValid, NoValid) {
    fa::Automaton fa;

    EXPECT_FALSE(fa.isValid());
}

TEST(AutomatonIsValid, OnlyOneSymbol) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_FALSE(fa.isValid());
}

TEST(AutomatonIsValid, OnlyOneState) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_FALSE(fa.isValid());
}

TEST(AutomatonIsValid, Valid) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.isValid());

}

// --- TEST AutomatonAddSymbol ---

TEST(AutomatonAddSymbol, AddSymbol) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.hasSymbol('a'));
}

TEST(AutomatonAddSymbol, AddSameSymbol) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.hasSymbol('a'));

    EXPECT_FALSE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.hasSymbol('a'));
}

TEST(AutomatonAddSymbol, AddEpsilon) {
    fa::Automaton fa;

    EXPECT_FALSE(fa.addSymbol(fa::Epsilon));
    EXPECT_FALSE(fa.hasSymbol(fa::Epsilon));
}

TEST(AutomatonAddSymbol, AddNonASCIISymbol) {
    fa::Automaton fa;

    EXPECT_FALSE(fa.addSymbol('\n'));
    EXPECT_FALSE(fa.hasSymbol('\n'));
}

TEST(AutomatonAddSymbol, AddSpaceSymbol) {
    fa::Automaton fa;

    EXPECT_FALSE(fa.addSymbol(' '));
    EXPECT_FALSE(fa.hasSymbol(' '));
}

// --- TEST AutomatonRemoveSymbol ---

TEST(AutomatonRemoveSymbol, RemoveSymbol) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.hasSymbol('a'));
    EXPECT_TRUE(fa.removeSymbol('a'));
    EXPECT_FALSE(fa.hasSymbol('a'));
}

TEST(AutomatonRemoveSymbol, RemoveSameSymbol) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.hasSymbol('a'));

    EXPECT_TRUE(fa.removeSymbol('a'));
    EXPECT_FALSE(fa.hasSymbol('a'));

    EXPECT_FALSE(fa.removeSymbol('a'));
    EXPECT_FALSE(fa.hasSymbol('a'));
}

TEST(AutomatonRemoveSymbol, RemoveUnknownSymbol) {
    fa::Automaton fa;

    EXPECT_FALSE(fa.removeSymbol('a'));
}

TEST(AutomatonRemoveSymbol, RemoveSymbolInTransition) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addTransition(1, 'a', 2));

    EXPECT_TRUE(fa.removeSymbol('a'));
    EXPECT_FALSE(fa.hasSymbol('a'));
    EXPECT_FALSE(fa.hasTransition(1, 'a', 2));
}

// --- TEST AutomatonAddState ---

TEST(AutomatonAddState, AddState) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
}

TEST(AutomatonAddState, AddSameState) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.hasState(1));

    EXPECT_FALSE(fa.addState(1));
    EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonAddState, AddNegativeState) {
    fa::Automaton fa;

    EXPECT_FALSE(fa.addState(-1));
    EXPECT_FALSE(fa.hasState(-1));
}

TEST(AutomatonAddState, AddMaxIntState) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(2147483647));
}

// TODO KeepState

// --- TEST AutomatonSetStateInitial ---

TEST(AutomatonSetStateInitial, OneInitialState) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    fa.setStateInitial(1);
    EXPECT_TRUE(fa.isStateInitial(1));
}

TEST(AutomatonSetStateInitial, UnknownState) {
    fa::Automaton fa;

    fa.setStateInitial(1);
    EXPECT_FALSE(fa.isStateInitial(1));
}

TEST(AutomatonSetStateInitial, RemoveState) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    fa.setStateInitial(1);
    EXPECT_TRUE(fa.isStateInitial(1));

    EXPECT_TRUE(fa.removeState(1));
    fa.setStateInitial(1);
    EXPECT_FALSE(fa.isStateInitial(1));
}

// TODO ReadEmptyString

// --- TEST AutomatonSetStateFinal ---

TEST(AutomatonSetStateFinal, OneFinalState) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    fa.setStateFinal(1);
    EXPECT_TRUE(fa.isStateFinal(1));
}

TEST(AutomatonSetStateFinal, UnknownState) {
    fa::Automaton fa;

    fa.setStateFinal(1);
    EXPECT_FALSE(fa.isStateFinal(1));
}

TEST(AutomatonSetStateFinal, RemoveState) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    fa.setStateFinal(1);
    EXPECT_TRUE(fa.isStateFinal(1));

    EXPECT_TRUE(fa.removeState(1));
    fa.setStateFinal(1);
    EXPECT_FALSE(fa.isStateFinal(1));
}

// --- TEST AutomatonAddTransition ---

TEST(AutomatonAddTransition, AddTransition) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));

    EXPECT_TRUE(fa.addSymbol('a'));

    EXPECT_TRUE(fa.addTransition(1, 'a', 2));
    EXPECT_TRUE(fa.hasTransition(1, 'a', 2));
}

TEST(AutomatonAddTransition, SameState) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));

    EXPECT_TRUE(fa.addSymbol('a'));

    EXPECT_TRUE(fa.addTransition(1, 'a', 1));
    EXPECT_TRUE(fa.hasTransition(1, 'a', 1));
}

TEST(AutomatonAddTransition, SameOriginAndLetter) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));

    EXPECT_TRUE(fa.addSymbol('a'));

    EXPECT_TRUE(fa.addTransition(1, 'a', 2));
    EXPECT_TRUE(fa.hasTransition(1, 'a', 2));

    EXPECT_TRUE(fa.addTransition(1, 'a', 3));
    EXPECT_TRUE(fa.hasTransition(1, 'a', 3));
}

TEST(AutomatonAddTransition, SameOriginAndDestination) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));

    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));

    EXPECT_TRUE(fa.addTransition(1, 'a', 2));
    EXPECT_TRUE(fa.hasTransition(1, 'a', 2));

    EXPECT_TRUE(fa.addTransition(1, 'b', 2));
    EXPECT_TRUE(fa.hasTransition(1, 'b', 2));
}

TEST(AutomatonAddTransition, SameLetterAndDestination) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));

    EXPECT_TRUE(fa.addSymbol('a'));

    EXPECT_TRUE(fa.addTransition(1, 'a', 3));
    EXPECT_TRUE(fa.hasTransition(1, 'a', 3));

    EXPECT_TRUE(fa.addTransition(2, 'a', 3));
    EXPECT_TRUE(fa.hasTransition(2, 'a', 3));
}

TEST(AutomatonAddTransition, SameTransition) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));

    EXPECT_TRUE(fa.addSymbol('a'));

    EXPECT_TRUE(fa.addTransition(1, 'a', 2));
    EXPECT_TRUE(fa.hasTransition(1, 'a', 2));

    EXPECT_FALSE(fa.addTransition(1, 'a', 2));
    EXPECT_TRUE(fa.hasTransition(1, 'a', 2));
}

TEST(AutomatonAddTransition, UnknownOrigin) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(2));

    EXPECT_TRUE(fa.addSymbol('a'));

    EXPECT_FALSE(fa.addTransition(1, 'a', 2));
    EXPECT_FALSE(fa.hasTransition(1, 'a', 2));
}

TEST(AutomatonAddTransition, UnknownTarget) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(2));

    EXPECT_TRUE(fa.addSymbol('a'));

    EXPECT_FALSE(fa.addTransition(2, 'a', 1));
    EXPECT_FALSE(fa.hasTransition(2, 'a', 1));
}

// TODO EpsilonEcoffet

// TODO EpsilonLeonard

// --- TEST AutomatonRemoveStateTest ---

TEST(AutomatonRemoveState, OneState) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.hasState(1));

    EXPECT_TRUE(fa.removeState(1));
    EXPECT_FALSE(fa.hasState(1));
}

TEST(AutomatonRemoveState, ManyStates) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));
    EXPECT_TRUE(fa.hasState(1));
    EXPECT_TRUE(fa.hasState(2));
    EXPECT_TRUE(fa.hasState(3));

    EXPECT_TRUE(fa.removeState(2));
    EXPECT_FALSE(fa.hasState(2));
    EXPECT_TRUE(fa.hasState(1));
    EXPECT_TRUE(fa.hasState(3));

    EXPECT_TRUE(fa.removeState(1));
    EXPECT_FALSE(fa.hasState(1));
    EXPECT_TRUE(fa.hasState(3));

    EXPECT_TRUE(fa.removeState(3));
    EXPECT_FALSE(fa.hasState(3));
}

TEST(AutomatonRemoveState, UnknownState) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.hasState(1));

    EXPECT_FALSE(fa.removeState(2));
    EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonRemoveState, OriginInTransition) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));

    EXPECT_TRUE(fa.addSymbol('a'));

    EXPECT_TRUE(fa.addTransition(1, 'a', 2));
    EXPECT_TRUE(fa.hasTransition(1, 'a', 2));

    EXPECT_TRUE(fa.removeState(1));
    EXPECT_FALSE(fa.hasState(1));
    EXPECT_FALSE(fa.hasTransition(1, 'a', 2));
}

TEST(AutomatonRemoveState, DestinationInTransition) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));

    EXPECT_TRUE(fa.addSymbol('a'));

    EXPECT_TRUE(fa.addTransition(2, 'a', 1));
    EXPECT_TRUE(fa.hasTransition(2, 'a', 1));

    EXPECT_TRUE(fa.removeState(1));
    EXPECT_FALSE(fa.hasState(1));
    EXPECT_FALSE(fa.hasTransition(2, 'a', 1));
}

TEST(AutomatonRemoveState, OriginAndDestinationInTransition) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));

    EXPECT_TRUE(fa.addSymbol('a'));

    EXPECT_TRUE(fa.addTransition(2, 'a', 1));
    EXPECT_TRUE(fa.hasTransition(2, 'a', 1));

    EXPECT_TRUE(fa.removeState(1));
    EXPECT_FALSE(fa.hasState(1));

    EXPECT_TRUE(fa.removeState(2));
    EXPECT_FALSE(fa.hasState(2));

    EXPECT_FALSE(fa.hasTransition(2, 'a', 1));
}

// --- AutomatonRemoveTransition ---

TEST(AutomatonRemoveTransition, OneTransition) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));

    EXPECT_TRUE(fa.addSymbol('a'));

    EXPECT_TRUE(fa.addTransition(1, 'a', 2));
    EXPECT_TRUE(fa.hasTransition(1, 'a', 2));

    EXPECT_TRUE(fa.removeTransition(1, 'a', 2));
    EXPECT_FALSE(fa.hasTransition(1, 'a', 2));
}

TEST(AutomatonRemoveTransition, UnknownOrigin) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));

    EXPECT_TRUE(fa.addSymbol('a'));

    EXPECT_TRUE(fa.addTransition(1, 'a', 2));
    EXPECT_TRUE(fa.hasTransition(1, 'a', 2));

    EXPECT_FALSE(fa.removeTransition(3, 'a', 2));
    EXPECT_TRUE(fa.hasTransition(1, 'a', 2));
}

TEST(AutomatonRemoveTransition, UnknownTarget) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));

    EXPECT_TRUE(fa.addSymbol('a'));

    EXPECT_TRUE(fa.addTransition(1, 'a', 2));
    EXPECT_TRUE(fa.hasTransition(1, 'a', 2));

    EXPECT_FALSE(fa.removeTransition(1, 'a', 3));
    EXPECT_TRUE(fa.hasTransition(1, 'a', 2));
}

// TODO RemoveAll

TEST(AutomatonWTF, ZombieStateResurrection) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addTransition(1, 'a', 2));

    EXPECT_TRUE(fa.removeState(2));
    EXPECT_FALSE(fa.hasTransition(1, 'a', 2));

    EXPECT_TRUE(fa.addState(2));

    EXPECT_FALSE(fa.hasTransition(1, 'a', 2));
}

// --- AutomatonHasEpsilonTransition ---

TEST(AutomatonHasEpsilonTransition, Whitout) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));

    EXPECT_TRUE(fa.addSymbol('a'));

    fa.setStateInitial(0);
    fa.setStateFinal(1);

    EXPECT_TRUE(fa.addTransition(0,'a',1));
    EXPECT_FALSE(fa.hasEpsilonTransition());
}

TEST(AutomatonHasEpsilonTransition, With){
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));

    fa.setStateInitial(0);
    fa.setStateFinal(1);

    EXPECT_TRUE(fa.addTransition(0,fa::Epsilon,1));
    EXPECT_TRUE(fa.hasEpsilonTransition());
}

TEST(AutomatonHasEpsilonTransition, AddAndRemove){
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(0));
    EXPECT_TRUE(fa.addState(1));

    fa.setStateInitial(0);
    fa.setStateFinal(1);

    EXPECT_TRUE(fa.addTransition(0,fa::Epsilon,1));
    EXPECT_TRUE(fa.hasEpsilonTransition());

    EXPECT_TRUE(fa.removeTransition(0,fa::Epsilon,1));
    EXPECT_FALSE(fa.hasEpsilonTransition());
}

// TODO AddAndRemoveStateToZavarsky

TEST(AutomatonWTF, EpsilonSelfLoopOfDeath) {
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    fa.setStateInitial(1);

    EXPECT_TRUE(fa.addSymbol('a'));
    
    EXPECT_TRUE(fa.addTransition(1, fa::Epsilon, 1));
    
    EXPECT_TRUE(fa.hasEpsilonTransition());

    EXPECT_FALSE(fa.isDeterministic());
}

// --- AutomatonIsDeterministic ---

TEST(AutomatonIsDeterministic, IsDeterministic){
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));

    EXPECT_TRUE(fa.addSymbol('a'));

    fa.setStateInitial(1);
    fa.setStateFinal(2);

    EXPECT_TRUE(fa.addTransition(1,'a',2));
    EXPECT_TRUE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministic, TwoTransitionsSameSymbol){
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));

    EXPECT_TRUE(fa.addSymbol('a'));

    fa.setStateInitial(1);
    fa.setStateFinal(2);

    EXPECT_TRUE(fa.addTransition(1,'a',2));
    EXPECT_TRUE(fa.addTransition(1,'a',3));
    EXPECT_FALSE(fa.isDeterministic());
}

// TODO GoodChahat

// TODO GoodVillemin

TEST(AutomatonIsDeterministic, TwoInitialStates){
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));

    EXPECT_TRUE(fa.addSymbol('a'));

    fa.setStateInitial(1);
    fa.setStateInitial(2);
    fa.setStateFinal(2);

    EXPECT_TRUE(fa.addTransition(1,'a',2));
    EXPECT_FALSE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministic, NoInitialState){
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));

    EXPECT_TRUE(fa.addSymbol('a'));

    fa.setStateFinal(2);

    EXPECT_TRUE(fa.addTransition(1,'a',2));
    EXPECT_FALSE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministic, NoFinalState){
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));

    EXPECT_TRUE(fa.addSymbol('a'));

    fa.setStateInitial(1);

    EXPECT_TRUE(fa.addTransition(1,'a',2));
    EXPECT_TRUE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministic, LonelyState){
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));

    EXPECT_TRUE(fa.addSymbol('a'));

    fa.setStateInitial(1);
    fa.setStateFinal(2);

    EXPECT_TRUE(fa.addTransition(1,'a',2));
    EXPECT_TRUE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministic, TwoFinalState){
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));

    EXPECT_TRUE(fa.addSymbol('a'));
    EXPECT_TRUE(fa.addSymbol('b'));

    fa.setStateInitial(1);
    fa.setStateFinal(2);
    fa.setStateFinal(3);

    EXPECT_TRUE(fa.addTransition(1,'a',2));
    EXPECT_TRUE(fa.addTransition(1,'b',3));
    EXPECT_TRUE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministic, WithoutTransition){
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));

    fa.setStateInitial(1);
    fa.setStateFinal(1);

    EXPECT_TRUE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministic, EpsilonTransition){
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));

    fa.setStateInitial(1);
    fa.setStateFinal(2);

    EXPECT_TRUE(fa.addTransition(1,fa::Epsilon,2));
    EXPECT_FALSE(fa.isDeterministic());
}

// --- AutomatonIsComplete ---

TEST(AutomatonIsComplete, Good){
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));

    EXPECT_TRUE(fa.addSymbol('a'));

    fa.setStateInitial(1);
    fa.setStateFinal(2);

    EXPECT_TRUE(fa.addTransition(1,'a',2));
    EXPECT_TRUE(fa.addTransition(2,'a',2));

    EXPECT_TRUE(fa.isComplete());
}

TEST(AutomatonIsComplete, NotGood){
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));

    EXPECT_TRUE(fa.addSymbol('a'));

    fa.setStateInitial(1);
    fa.setStateFinal(2);

    EXPECT_TRUE(fa.addTransition(1,'a',2));

    EXPECT_FALSE(fa.isComplete());
}

TEST(AutomatonIsComplete, ZeroTransition){
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));

    EXPECT_TRUE(fa.addSymbol('a'));

    fa.setStateInitial(1);
    fa.setStateFinal(1);

    EXPECT_TRUE(fa.addTransition(1,'a',1));

    EXPECT_TRUE(fa.isComplete());
}

TEST(AutomatonIsComplete, AddAndRemoveTransition){
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));

    EXPECT_TRUE(fa.addSymbol('a'));

    fa.setStateInitial(1);
    fa.setStateFinal(2);

    EXPECT_TRUE(fa.addTransition(1,'a',2));
    EXPECT_FALSE(fa.isComplete());

    EXPECT_TRUE(fa.addTransition(2,'a',2));
    EXPECT_TRUE(fa.isComplete());

    EXPECT_TRUE(fa.removeTransition(2,'a',2));
    EXPECT_FALSE(fa.isComplete());
}

TEST(AutomatonIsComplete, LonelyState){
    fa::Automaton fa;

    EXPECT_TRUE(fa.addState(1));
    EXPECT_TRUE(fa.addState(2));
    EXPECT_TRUE(fa.addState(3));

    EXPECT_TRUE(fa.addSymbol('a'));

    fa.setStateInitial(1);
    fa.setStateFinal(2);

    EXPECT_TRUE(fa.addTransition(1,'a',2));
    EXPECT_FALSE(fa.isComplete());
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}