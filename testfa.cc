
#include "gtest/gtest.h"

#include "Automaton.h"

/**
 * Attendu : la fonction ne considère pas l'automate comme valide
 */
TEST(Valid, isNotValid) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isValid());
}

/**
 * Attendu : le symbole a été correctement ajouté
 */
TEST(Symbol, addSymbol) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('a'));
}

/**
 * Attendu : le symbol espace n'est pas rajouté
 */
TEST(Symbol, addSymbolSpace) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.addSymbol(' '));
  EXPECT_FALSE(fa.hasSymbol(' '));
}

/**
 * Attendu : le symbol espace n'est pas rajouté
 */
TEST(Symbol, addEpsilon) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol(fa::Epsilon));
  EXPECT_TRUE(fa.hasSymbol(fa::Epsilon));
}


/**
 * Attendu : le symbole a été correctement supprimé
 */
TEST(Symbol, removeSymbol) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.removeSymbol('a'));
  EXPECT_FALSE(fa.hasSymbol('a'));
}

/**
 * Attendu : supprimé un symbole qui n'existe pas
 */
TEST(Symbol, removeSymbolDontExist) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeSymbol('a'));
}

/**
 * Attendue : le nombre de symbole est égale à un
 */
TEST(Symbol, countOneSymbol) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_EQ(fa.countSymbols(), static_cast<size_t>(1));
}

/**
 * Attendue : le nombre de symbole est égale à 0
 */
TEST(Symbol, countZeroSymbol) {
  fa::Automaton fa;
  EXPECT_EQ(fa.countSymbols(), static_cast<size_t>(0));
}


/**
 * Attendue : le nombre de symbole est égale à 2
 */
TEST(Symbol, countTwoSymbol) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_EQ(fa.countSymbols(), static_cast<size_t>(2));
}

/**
 * Attendue : le nombre de symbole est égale à 1 pour éviter les doublons
 */
TEST(Symbol, addSameSymbol) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_FALSE(fa.addSymbol('a'));
  EXPECT_EQ(fa.countSymbols(), static_cast<size_t>(1));
}

/**
 * Attendue : ajout d'un état
 */
TEST(State, addState) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.hasState(1));
}

/**
 * Attendu : l'état a été correctement supprimé
 */
TEST(State, removeState) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.removeState(1));
  EXPECT_FALSE(fa.hasState(1));
}

/**
 * Attendu : supprimé un état qui n'existe pas
 */
TEST(State, removeStateDontExist) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeSymbol(1));
}

/**
 * Attendue : le nombre d'état est égale à 1
 */
TEST(State, countOneState) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_EQ(fa.countSymbols(), static_cast<size_t>(1));
}

/**
 * Attendue : le nombre d'état est égale à 0
 */
TEST(State, countZeroState) {
  fa::Automaton fa;
  EXPECT_EQ(fa.countStates(), static_cast<size_t>(0));
}


/**
 * Attendue : le nombre d'état est égale à 2
 */
TEST(State, countTwoState) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_EQ(fa.countStates(), static_cast<size_t>(2));
}

/**
 * Attendue : le nombre d'état est égale à 1 pour éviter les doublons
 */
TEST(State, addSameState) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_FALSE(fa.addState(1));
  EXPECT_EQ(fa.countStates(), static_cast<size_t>(1));
}

/**
 * Attendue : ajout d'un état initial
 */
TEST(Initial, isInitial) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));
}

/**
 * Attendue : un état non initial
 */
TEST(Initial, isNotInitial) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_FALSE(fa.isStateInitial(1));
}

/**
 * Attendue : un état qui n'existe pas
 */
TEST(Initial, isInitialDontExist) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isStateInitial(1));
}

/**
 * Attendue : un état qui n'existe pas
 */
TEST(Initial, setInitialDontExist) {
  fa::Automaton fa;
  fa.setStateInitial(1);
  EXPECT_FALSE(fa.isStateInitial(1));
}

/**
 * Attendue : ajout d'un état initial
 */
TEST(Final, setFinal) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
}

/**
 * Attendue : un état non initial
 */
TEST(Final, isNotFinal) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isStateFinal(1));
}

/**
 * Attendue : un état qui n'existe pas
 */
TEST(Final, isFinalDontExist) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isStateFinal(1));
}

/**
 * Attendue : un état qui n'existe pas
 */
TEST(Final, setFinalDontExist) {
  fa::Automaton fa;
  fa.setStateFinal(1);
  EXPECT_FALSE(fa.isStateFinal(1));
}

/**
 * Attendu : la transition a été correctement ajouté
 */
TEST(Transition, addTransition) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.hasTransition(1, 'a', 2));
}

/**
 * Attendu : la transition a été correctement supprimé
 */
TEST(Transition, removeTransition) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.removeTransition(1, 'a', 2));
  EXPECT_FALSE(fa.hasTransition(1, 'a', 2));
}

/**
 * Attendu : supprimé une transition qui n'existe pas
 */
TEST(Transition, removeTransitionDontExist) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeTransition(1, 'a', 2));
}

/**
 * Attendu : le nombre de symbole est égale à un
 */
TEST(Transition, countOneTransition) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_EQ(fa.countTransitions(), static_cast<size_t>(1));
}

/**
 * Attendu : le nombre de symbole est égale à 0
 */
TEST(Transition, countZeroTransition) {
  fa::Automaton fa;
  EXPECT_EQ(fa.countTransitions(), static_cast<size_t>(0));
}


/**
 * Attendu : le nombre de symbole est égale à 2
 */
TEST(Transition, countTwoTransition) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'a', 1));
  EXPECT_EQ(fa.countTransitions(), static_cast<size_t>(2));
}

/**
 * Attendu : le nombre de transition est égale à 1 pour éviter les doublons
 */
TEST(Transition, addSameTransition) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_FALSE(fa.addTransition(1, 'a', 2));
  EXPECT_EQ(fa.countTransitions(), static_cast<size_t>(1));
}

/**
 * Attendu : l'automate est valide
 */
TEST(Valid, isValid) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.isValid());
}

/**
 * Attendu : il y a un epsilone transition
 */
TEST(Epsilon, hasEpsilon) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol(fa::Epsilon));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addTransition(1, fa::Epsilon, 2));
  EXPECT_TRUE(fa.hasEpsilonTransition());
}

/**
 * Attendu : il n'y a pas d'epsilone transition
 */
TEST(Epsilon, HasNotEpsilon) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_FALSE(fa.hasEpsilonTransition());
}

/**
 * Attendu : il y a un epsilon mais pas de transition
 */
TEST(Epsilon, HasNotEpsilonTransition) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol(fa::Epsilon));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_FALSE(fa.hasEpsilonTransition());
}

/**
 * Attendu : l'automate est déterministe 
 */
TEST(Deterministic, isDeterministic) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.isDeterministic());
}

/**
 * Attendu : l'automate n'est pas déterministe 
 */
TEST(Deterministic, isNotDeterministic) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 3));
  EXPECT_FALSE(fa.isDeterministic());
}

/**
 * Attendu : l'automate est complet
 */
TEST(Complete, isComplete) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'a', 1));
  EXPECT_TRUE(fa.isComplete());
  fa.prettyPrint(std::cout);
}

/**
 * Attendu : l'automate n'est pas complet
 */
TEST(Complete, isNotCompleteSymbol) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_FALSE(fa.isComplete());
}

/**
 * Attendu : l'automate n'est pas complet
 */
TEST(Complete, test_isComplete_non_state) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_FALSE(fa.isComplete());
}

// TODO état avec transitions aa e

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
