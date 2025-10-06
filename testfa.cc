
#include "gtest/gtest.h"

#include "Automaton.h"

/**
 * Attendu : la fonction ne considère pas l'automate comme valide
 */
TEST(AutomatonTP1, test_isValid_normal) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isValid());
}

/**
 * Attendu : le symbole a été correctement ajouté
 */
TEST(AutomatonTP1, test_addSymbol_normal) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('a'));
}

/**
 * Attendu : le symbol espace n'est pas rajouté
 */
TEST(AutomatonTP1, test_addSymbol_espace) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol(' '));
  EXPECT_TRUE(fa.hasSymbol(' '));
}


/**
 * Attendu : le symbole a été correctement supprimé
 */
TEST(AutomatonTP1, test_removeSymbol_normal) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.removeSymbol('a'));
  EXPECT_FALSE(fa.hasSymbol('a'));
}

/**
 * Attendu : supprimé un symbole qui n'existe pas
 */
TEST(AutomatonTP1, test_removeSymbol_existePas) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeSymbol('a'));
}

/**
 * Attendue : le nombre de symbole est égale à un
 */
TEST(AutomatonTP1, test_countSymbols_1) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_EQ(fa.countSymbols(), static_cast<size_t>(1));
}

/**
 * Attendue : le nombre de symbole est égale à 0
 */
TEST(AutomatonTP1, test_countSymbols_0) {
  fa::Automaton fa;
  EXPECT_EQ(fa.countSymbols(), static_cast<size_t>(0));
}


/**
 * Attendue : le nombre de symbole est égale à 2
 */
TEST(AutomatonTP1, test_countSymbols_2) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_EQ(fa.countSymbols(), static_cast<size_t>(2));
}

/**
 * Attendue : le nombre de symbole est égale à 1 pour éviter les doublons
 */
TEST(AutomatonTP1, test_addSymbol_memeSymbol) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_FALSE(fa.addSymbol('a'));
  EXPECT_EQ(fa.countSymbols(), static_cast<size_t>(1));
}

/**
 * Attendue : ajout d'un état
 */
TEST(AutomatonTP1, test_addState_normal) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.hasState(1));
}

/**
 * Attendu : l'état a été correctement supprimé
 */
TEST(AutomatonTP1, test_removeState_normal) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.removeState(1));
  EXPECT_FALSE(fa.hasState(1));
}

/**
 * Attendu : supprimé un état qui n'existe pas
 */
TEST(AutomatonTP1, test_removeState_existePas) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeSymbol(1));
}

/**
 * Attendue : le nombre d'état est égale à 1
 */
TEST(AutomatonTP1, test_countStates_1) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_EQ(fa.countSymbols(), static_cast<size_t>(1));
}

/**
 * Attendue : le nombre d'état est égale à 0
 */
TEST(AutomatonTP1, test_countStates_0) {
  fa::Automaton fa;
  EXPECT_EQ(fa.countStates(), static_cast<size_t>(0));
}


/**
 * Attendue : le nombre d'état est égale à 2
 */
TEST(AutomatonTP1, test_countStates_2) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_EQ(fa.countStates(), static_cast<size_t>(2));
}

/**
 * Attendue : le nombre d'état est égale à 1 pour éviter les doublons
 */
TEST(AutomatonTP1, test_addState_memeEtat) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_FALSE(fa.addState(1));
  EXPECT_EQ(fa.countStates(), static_cast<size_t>(1));
}

/**
 * Attendue : ajout d'un état initial
 */
TEST(AutomatonTP1, test_setStateInitial_normal) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));
}

/**
 * Attendue : un état non initial
 */
TEST(AutomatonTP1, test_isStateInitial_non) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_FALSE(fa.isStateInitial(1));
}

/**
 * Attendue : un état qui n'existe pas
 */
TEST(AutomatonTP1, test_isStateInitial_existePas) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isStateInitial(1));
}

/**
 * Attendue : un état qui n'existe pas
 */
TEST(AutomatonTP1, test_setStateInitial_existePas) {
  fa::Automaton fa;
  fa.setStateInitial(1);
  EXPECT_FALSE(fa.isStateInitial(1));
}

/**
 * Attendue : ajout d'un état initial
 */
TEST(AutomatonTP1, test_setStateFinal_normal) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
}

/**
 * Attendue : un état non initial
 */
TEST(AutomatonTP1, test_isStateFinal_non) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isStateFinal(1));
}

/**
 * Attendue : un état qui n'existe pas
 */
TEST(AutomatonTP1, test_isStateFinal_existePas) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isStateFinal(1));
}

/**
 * Attendue : un état qui n'existe pas
 */
TEST(AutomatonTP1, test_setStateFinal_existePas) {
  fa::Automaton fa;
  fa.setStateFinal(1);
  EXPECT_FALSE(fa.isStateFinal(1));
}

/**
 * Attendu : la transition a été correctement ajouté
 */
TEST(AutomatonTP1, test_addTransition_normal) {
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
TEST(AutomatonTP1, test_removeTransition_normal) {
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
TEST(AutomatonTP1, test_removeTransition_existePas) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeTransition(1, 'a', 2));
}

/**
 * Attendu : le nombre de symbole est égale à un
 */
TEST(AutomatonTP1, test_countTransition_1) {
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
TEST(AutomatonTP1, test_countTransition_0) {
  fa::Automaton fa;
  EXPECT_EQ(fa.countTransitions(), static_cast<size_t>(0));
}


/**
 * Attendu : le nombre de symbole est égale à 2
 */
TEST(AutomatonTP1, test_countTransitions_2) {
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
TEST(AutomatonTP1, test_addTransition_memeTransition) {
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
TEST(AutomatonTP1, test_isValid) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.isValid());
}

/**
 * Attendu : il y a un epsilone transition
 */
TEST(AutomatonTP2, test_hasEpsilonTransition_oui) {
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
TEST(AutomatonTP2, test_hasEpsilonTransition_non) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_FALSE(fa.hasEpsilonTransition());
}

/**
 * Attendu : l'automate est déterministe 
 */
TEST(AutomatonTP2, test_isDeterministic_oui) {
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
TEST(AutomatonTP2, test_isDeterministic_non) {
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
TEST(AutomatonTP2, test_isComplete_oui) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.isComplete());
}

/**
 * Attendu : l'automate n'est pas complet
 */
TEST(AutomatonTP2, test_isComplete_non) {
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
TEST(AutomatonTP2, test_isComplete_non_symbol) {
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
TEST(AutomatonTP2, test_isComplete_non_state) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_FALSE(fa.isComplete());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
