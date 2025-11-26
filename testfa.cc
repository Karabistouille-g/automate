
#include "gtest/gtest.h"

#include "Automaton.h"

#include <iostream>

/**
 * Attendu : la fonction ne considère pas l'automate comme valide
 */
TEST(Valid, isNotValid)
{
  fa::Automaton fa;
  EXPECT_FALSE(fa.isValid());
}

/**
 * Attendu : le symbole a été correctement ajouté
 */
TEST(AddSymbol, addSymbol)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('a'));
}

/**
 * Attendu : le symbol espace n'est pas rajouté
 */
TEST(AddSymbol, addSymbolSpace)
{
  fa::Automaton fa;
  EXPECT_FALSE(fa.addSymbol(' '));
  EXPECT_FALSE(fa.hasSymbol(' '));
}

/**
 * Attendu : on ne peut pas rajouter un state négatif
 */
TEST(AddSymbol, addNegativeState)
{
  fa::Automaton fa;
  EXPECT_FALSE(fa.addState(-1));
  EXPECT_FALSE(fa.hasState(-1));
}

/**
 * Attendu : n'accepte pas les symbols non ascii
 */
TEST(AddSymbol, addNonASCII)
{
  fa::Automaton fa;
  EXPECT_FALSE(fa.addSymbol('\n'));
  EXPECT_FALSE(fa.hasSymbol('\n'));
}

/**
 * Attendu : le symbole a été correctement supprimé
 */
TEST(RemoveSymbol, removeSymbol)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.removeSymbol('a'));
  EXPECT_FALSE(fa.hasSymbol('a'));
}

/**
 * Attendu : supprimé un symbole qui n'existe pas
 */
TEST(RemoveSymbol, removeSymbolDontExist)
{
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeSymbol('a'));
}

/**
 * Attendue : le nombre de symbole est égale à un
 */
TEST(Symbol, countOneSymbol)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_EQ(fa.countSymbols(), static_cast<size_t>(1));
}

/**
 * Attendue : le nombre de symbole est égale à 0
 */
TEST(Symbol, countZeroSymbol)
{
  fa::Automaton fa;
  EXPECT_EQ(fa.countSymbols(), static_cast<size_t>(0));
}

/**
 * Attendue : le nombre de symbole est égale à 2
 */
TEST(Symbol, countTwoSymbol)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_EQ(fa.countSymbols(), static_cast<size_t>(2));
}

/**
 * Attendue : le nombre de symbole est égale à 1 pour éviter les doublons
 */
TEST(AddSymbol, addSameSymbol)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_FALSE(fa.addSymbol('a'));
  EXPECT_EQ(fa.countSymbols(), static_cast<size_t>(1));
}

/**
 * Attendue : supprimer les transitions qui ont le symbol supprimer
 */
TEST(RemoveSymbol, removeSymbolInTransition)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));
  EXPECT_TRUE(fa.removeSymbol('b'));
  EXPECT_EQ(fa.countSymbols(), static_cast<size_t>(1));
  EXPECT_FALSE(fa.hasTransition(2, 'b', 1));
}

/**
 * Attendue : ajout d'un état
 */
TEST(AddState, addState)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.hasState(1));
}

/**
 * Attendu : l'état a été correctement supprimé
 */
TEST(RemoveState, removeState)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.removeState(1));
  EXPECT_FALSE(fa.hasState(1));
}

/**
 * Attendu : supprimé un état qui n'existe pas
 */
TEST(RemoveState, removeStateDontExist)
{
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeState(1));
}

/**
 * Attendue : le nombre d'état est égale à 1
 */
TEST(State, countOneState)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState('a'));
  EXPECT_EQ(fa.countStates(), static_cast<size_t>(1));
}

/**
 * Attendue : le nombre d'état est égale à 0
 */
TEST(State, countZeroState)
{
  fa::Automaton fa;
  EXPECT_EQ(fa.countStates(), static_cast<size_t>(0));
}

/**
 * Attendue : le nombre d'état est égale à 2
 */
TEST(State, countTwoState)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_EQ(fa.countStates(), static_cast<size_t>(2));
}

/**
 * Attendue : le nombre d'état est égale à 1 pour éviter les doublons
 */
TEST(AddState, addSameState)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_FALSE(fa.addState(1));
  EXPECT_EQ(fa.countStates(), static_cast<size_t>(1));
}

/**
 * Attendue : l'état est supprimé avec toutes les transitions
 */
TEST(RemoveState, removeStateTransition)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'a', 1));
  EXPECT_TRUE(fa.removeState(2));
  EXPECT_FALSE(fa.hasTransition(1, 'a', 2));
  EXPECT_FALSE(fa.hasTransition(2, 'a', 1));
}

/**
 * Attendue : ajout d'un état initial
 */
TEST(Initial, isInitial)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));
}

/**
 * Attendue : un état non initial
 */
TEST(Initial, isNotInitial)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_FALSE(fa.isStateInitial(1));
}

/**
 * Attendue : un état qui n'existe pas
 */
TEST(Initial, isInitialDontExist)
{
  fa::Automaton fa;
  EXPECT_FALSE(fa.isStateInitial(1));
}

/**
 * Attendue : un état qui n'existe pas
 */
TEST(Initial, setInitialDontExist)
{
  fa::Automaton fa;
  fa.setStateInitial(1);
  EXPECT_FALSE(fa.isStateInitial(1));
}

/**
 * Attendue : ajout d'un état initial
 */
TEST(Final, setFinal)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
}

/**
 * Attendue : un état non initial
 */
TEST(Final, isNotFinal)
{
  fa::Automaton fa;
  EXPECT_FALSE(fa.isStateFinal(1));
}

/**
 * Attendue : un état qui n'existe pas
 */
TEST(Final, isFinalDontExist)
{
  fa::Automaton fa;
  EXPECT_FALSE(fa.isStateFinal(1));
}

/**
 * Attendue : un état qui n'existe pas
 */
TEST(Final, setFinalDontExist)
{
  fa::Automaton fa;
  fa.setStateFinal(1);
  EXPECT_FALSE(fa.isStateFinal(1));
}

/**
 * Attendu : la transition a été correctement ajouté
 */
TEST(AddTransition, addTransition)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.hasTransition(1, 'a', 2));
}

/**
 * Attendu : la transition ne se créer pas par manque d'origine
 */
TEST(AddTransition, addTransitionUnknowOrigin)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_FALSE(fa.addTransition(1, 'a', 2));
  EXPECT_FALSE(fa.hasTransition(1, 'a', 2));
}

/**
 * Attendu : la transition ne se créer pas par manque de destination
 */
TEST(AddTransition, addTransitionUnknowTarget)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_FALSE(fa.addTransition(2, 'a', 1));
  EXPECT_FALSE(fa.hasTransition(2, 'a', 1));
}

/**
 * Attendu : la transition ne se créer pas par manque de symbol
 */
TEST(AddTransition, addTransitionUnknowSymbol)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_FALSE(fa.addTransition(2, 'a', 1));
  EXPECT_FALSE(fa.hasTransition(2, 'a', 1));
}

/**
 * Attendu : la transition a été correctement supprimé
 */
TEST(RemoveTransition, removeTransition)
{
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
TEST(RemoveTransition, removeTransitionDontExist)
{
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeTransition(1, 'a', 2));
}

/**
 * Attendu : le nombre de symbole est égale à un
 */
TEST(CountTransition, countOneTransition)
{
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
TEST(CountTransition, countZeroTransition)
{
  fa::Automaton fa;
  EXPECT_EQ(fa.countTransitions(), static_cast<size_t>(0));
}

/**
 * Attendu : le nombre de symbole est égale à 2
 */
TEST(CountTransition, countTwoTransition)
{
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
TEST(AddTransition, addSameTransition)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_FALSE(fa.addTransition(1, 'a', 2));
  EXPECT_EQ(fa.countTransitions(), static_cast<size_t>(1));
}

/**
 * Attendu : ajouter une transition qui boucle sur le même état
 */
TEST(AddTransition, addTransitionSameState)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 1));
  EXPECT_EQ(fa.countTransitions(), static_cast<size_t>(1));
}

/**
 * Attendu : l'automate est valide
 */
TEST(Valid, isValid)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addSymbol('a'));
  fa.setStateInitial(1);
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isValid());
}

/**
 * Attendu : l'automate n'est pas valide
 */
TEST(Valid, isValidNoSymbol)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_FALSE(fa.isValid());
}

/**
 * Attendu : l'automate n'est pas valide
 */
TEST(Valid, isValidNoState)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_FALSE(fa.isValid());
}

/**
 * Attendu : il y a un epsilone transition
 */
TEST(Epsilon, hasEpsilon)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addTransition(1, fa::Epsilon, 2));
  EXPECT_TRUE(fa.hasEpsilonTransition());
}

/**
 * Attendu : il y a 2 epsilone transition
 */
TEST(Epsilon, hasEpsilonTwice)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addTransition(1, fa::Epsilon, 2));
  EXPECT_TRUE(fa.addTransition(2, fa::Epsilon, 1));
  EXPECT_TRUE(fa.hasEpsilonTransition());
}

/**
 * Attendu : il n'y a pas d'epsilone transition
 */
TEST(Epsilon, HasNotEpsilon)
{
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
TEST(Epsilon, HasNotEpsilonTransition)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_FALSE(fa.hasEpsilonTransition());
}

/**
 * Attendu : il y a un epsilon transition supprimé
 */
TEST(Epsilon, removeEpsilonTransition)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addTransition(1, fa::Epsilon, 2));
  EXPECT_TRUE(fa.hasEpsilonTransition());
  EXPECT_TRUE(fa.removeTransition(1, fa::Epsilon, 2));
  EXPECT_FALSE(fa.hasEpsilonTransition());
}

/**
 * Attendu : l'automate est déterministe
 */
TEST(Deterministic, isDeterministic)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.isDeterministic());
}

/**
 * Attendu : l'automate n'est pas déterministe car 0 state initial
 */
TEST(Deterministic, isDeterministicNoInitialState)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_FALSE(fa.isDeterministic());
}

/**
 * Attendu : l'automate n'est pas déterministe
 */
TEST(Deterministic, isNotDeterministic)
{
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
 * Attendu : l'automate n'est pas déterministe car 2 états initiaux
 */
TEST(Deterministic, isDeterministicWithTwoInitialState)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 2));
  EXPECT_TRUE(fa.addTransition(2, 'a', 1));
  EXPECT_TRUE(fa.addTransition(2, 'b', 1));

  EXPECT_TRUE(fa.addState(3));
  fa.setStateInitial(3);
  EXPECT_TRUE(fa.addTransition(3, 'a', 2));
  EXPECT_TRUE(fa.addTransition(3, 'b', 2));
  EXPECT_FALSE(fa.isDeterministic());
}

/**
 * Attendu : l'automate n'est pas déterministe car 2 états initiaux
 */
TEST(Deterministic, isDeterministicWithTwoFinalState)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  fa.setStateFinal(3);
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 1));
  EXPECT_TRUE(fa.addTransition(2, 'b', 1));
  EXPECT_TRUE(fa.addTransition(3, 'a', 1));
  EXPECT_TRUE(fa.addTransition(3, 'b', 1));
  EXPECT_TRUE(fa.isDeterministic());
}

/**
 * Attendu : un des états de l'automate est à l'ouest
 */
TEST(Deterministic, isDeterministicInOuest)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  fa.setStateInitial(1);
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isDeterministic());
}

/**
 * Attendu : l'automate est complet
 */
TEST(Complete, isComplete)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'a', 1));
  EXPECT_TRUE(fa.isComplete());
}

/**
 * Attendu : l'automate n'est pas complet
 */
TEST(Complete, isNotCompleteSymbol)
{
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
TEST(Complete, isNotCompleteState)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_FALSE(fa.isComplete());
}

/**
 * Attendu : l'automate n'est pas complet
 */
TEST(Mirror, createMirror)
{
  fa::Automaton fa;
  fa::Automaton mirror;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 3));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));
  EXPECT_TRUE(fa.addTransition(3, 'a', 3));
  EXPECT_TRUE(fa.addTransition(3, 'b', 3));
  mirror = fa.createMirror(fa);
  EXPECT_TRUE(mirror.isStateFinal(1));
  EXPECT_TRUE(mirror.isStateInitial(3));
  EXPECT_TRUE(mirror.hasTransition(2, 'a', 1));
  EXPECT_TRUE(mirror.hasTransition(3, 'b', 1));
  EXPECT_TRUE(mirror.hasTransition(3, 'a', 2));
  EXPECT_TRUE(mirror.hasTransition(2, 'b', 2));
  EXPECT_TRUE(mirror.hasTransition(3, 'a', 3));
  EXPECT_TRUE(mirror.hasTransition(3, 'b', 3));
  mirror.prettyPrint(std::cout);
}

/**
 * Attendu : retourne tous les états avec pour transitions un symbol donnée et une liste d'état donné
 */
TEST(MakeTransitions, makeTransitions)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  EXPECT_TRUE(fa.addState(5));
  EXPECT_TRUE(fa.addSymbol('a'));
  fa.setStateInitial(1);
  fa.setStateFinal(4);
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 5));
  EXPECT_TRUE(fa.addTransition(3, 'a', 4));
  EXPECT_TRUE(fa.addTransition(4, 'a', 5));
  std::set<int> initial;
  initial.insert(1);
  initial.insert(2);
  std::set<int> final;
  final.insert(2);
  final.insert(3);
  final.insert(5);
  EXPECT_EQ(fa.makeTransition(initial, 'a'), final);
}

/**
 * Attendu : retourne tous l'état final pour un mot donné
 */
TEST(ReadString, readString)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 3));
  std::set<int> final;
  final.insert(3);
  EXPECT_EQ(fa.readString("ab"), final);
}

/**
 * Attendu : retourne tous les états finaux pour un mot donné
 */
TEST(ReadString, readStringTwoFinalState)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  EXPECT_TRUE(fa.addState(5));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.setStateFinal(5);
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 3));
  EXPECT_TRUE(fa.addTransition(1, 'a', 4));
  EXPECT_TRUE(fa.addTransition(4, 'b', 5));
  std::set<int> final;
  final.insert(3);
  final.insert(5);
  EXPECT_EQ(fa.readString("ab"), final);
}

/**
 * Attendu : retourne l'état 2
 */
TEST(ReadString, readStringNoFinalState)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  EXPECT_TRUE(fa.addState(5));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addSymbol('c'));
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.setStateFinal(5);
  EXPECT_TRUE(fa.addTransition(1, 'c', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 3));
  EXPECT_TRUE(fa.addTransition(1, 'a', 4));
  EXPECT_TRUE(fa.addTransition(4, 'b', 5));
  std::set<int> final;
  final.insert(2);
  EXPECT_EQ(fa.readString("c"), final);
}

/**
 * Attendu : retourne rien
 */
TEST(ReadString, readStringNoTransition)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  EXPECT_TRUE(fa.addState(5));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addSymbol('c'));
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.setStateFinal(5);
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 3));
  EXPECT_TRUE(fa.addTransition(1, 'a', 4));
  EXPECT_TRUE(fa.addTransition(4, 'b', 5));
  std::set<int> final;
  EXPECT_EQ(fa.readString("c"), final);
}

/**
 * Attendu : retourne tous les états finaux pour un mot donné
 */
TEST(Match, match)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  EXPECT_TRUE(fa.addState(5));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.setStateFinal(5);
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 3));
  EXPECT_TRUE(fa.addTransition(1, 'a', 4));
  EXPECT_TRUE(fa.addTransition(4, 'b', 5));
  EXPECT_TRUE(fa.match("ab"));
}

/**
 * Attendu : retourne tous les états finaux pour un mot donné
 */
TEST(Match, noMatch)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  EXPECT_TRUE(fa.addState(5));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addSymbol('c'));
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.setStateFinal(5);
  EXPECT_TRUE(fa.addTransition(1, 'c', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 3));
  EXPECT_TRUE(fa.addTransition(1, 'a', 4));
  EXPECT_TRUE(fa.addTransition(4, 'b', 5));
  EXPECT_FALSE(fa.match("c"));
}

/**
 * Attendu : le langage est vide
 */
TEST(LanguageEmpty, isLanguageEmpty)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_FALSE(fa.isLanguageEmpty());
}

/**
 * Attendu : supprime les états non accessibles
 */
TEST(RemoveNonAccessible, removeNonAccessible)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addSymbol('a'));
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(3, 'a', 2));
  fa.removeNonAccessibleStates();
  EXPECT_FALSE(fa.hasState(3));
  EXPECT_FALSE(fa.hasTransition(3, 'a', 2));
}

/**
 * Attendu : supprime les états non co accessibles
 */
TEST(RemoveNonCoAccessible, removeNonCoAccessible)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addSymbol('a'));
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'a', 3));
  fa.removeNonCoAccessibleStates();
  EXPECT_FALSE(fa.hasState(3));
  EXPECT_FALSE(fa.hasTransition(3, 'a', 2));
}

/**
 * Attendu : créer un automate qui est l'intersection des 2 automates
 */
TEST(CreateIntersection, createIntersection)
{
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));

  fa::Automaton fo;
  EXPECT_TRUE(fo.addState(1));
  EXPECT_TRUE(fo.addState(2));
  EXPECT_TRUE(fo.addSymbol('a'));
  EXPECT_TRUE(fo.addSymbol('b'));
  fo.setStateInitial(1);
  fo.setStateFinal(2);
  EXPECT_TRUE(fo.addTransition(1, 'a', 1));
  EXPECT_TRUE(fo.addTransition(1, 'b', 2));
  EXPECT_TRUE(fo.addTransition(2, 'b', 2));
  EXPECT_TRUE(fo.addTransition(2, 'a', 1));

  fa::Automaton fao;
  EXPECT_TRUE(fao.addState(1));
  EXPECT_TRUE(fao.addState(2));
  EXPECT_TRUE(fao.addState(3));
  EXPECT_TRUE(fao.addSymbol('a'));
  EXPECT_TRUE(fao.addSymbol('b'));
  fao.setStateInitial(1);
  fao.setStateFinal(3);
  EXPECT_TRUE(fao.addTransition(1, 'a', 2));
  EXPECT_TRUE(fao.addTransition(2, 'a', 2));
  EXPECT_TRUE(fao.addTransition(2, 'b', 3));
  EXPECT_TRUE(fao.addTransition(3, 'b', 3));
  EXPECT_TRUE(fao.addTransition(3, 'a', 2));

  fa::Automaton newfao = fa.createIntersection(fa, fo);
}

TEST (LanguageEmpty, DeepGalland) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  for (int i = 3; i < 5000; i++) {
    EXPECT_TRUE(fa.addState(i));
    EXPECT_TRUE(fa.addTransition(i - 1, 'a', i));
    EXPECT_TRUE(fa.addTransition(i - 1, 'b', i));
  }
  EXPECT_TRUE(fa.addTransition(4999, 'a', 2));
  EXPECT_TRUE(fa.addTransition(4999, 'b', 2));
  EXPECT_TRUE(fa.isLanguageEmpty());
}

// TODO état avec transitions aa e

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// Test deux état initiaux avec isDeterminisc
// Test deux état finaux avec isDeterminisc