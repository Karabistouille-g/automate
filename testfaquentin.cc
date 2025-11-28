
#include "gtest/gtest.h"

#include "Automaton.h"

TEST(AutomatonisValidTest, EmptyAutomat) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isValid());
}
TEST(AutomatonisValidTest, EmptyStates) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_FALSE(fa.isValid());
}
TEST(AutomatonisValidTest, EmptySymboles) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(3));
  EXPECT_FALSE(fa.isValid());
}
TEST(AutomatonisValidTest, ValideAutomaton) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.isValid());
}

TEST(AutomatonAddSymbolTest, AddNotAASCIISymbole){
  fa::Automaton fa;
  EXPECT_FALSE(fa.addSymbol('\n'));
}

TEST(AutomatonAddStateTest, AddNegativeState){
  fa::Automaton fa;
  EXPECT_FALSE(fa.addState(-1));
}

TEST(AutomatonAddStateTest, AddIdenticalState){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_FALSE(fa.addState(0));
}

TEST(AutomatonAddStateTest, MaxState){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(2147483647));
}

TEST(AutomatonRemoveSymboldTest, RemoveOneSymbol) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addSymbol('c'));
  EXPECT_TRUE(fa.addSymbol('d'));
  EXPECT_TRUE(fa.removeSymbol('c'));
  EXPECT_EQ(3u,fa.countSymbols());
  
}

TEST(AutomatonRemoveSymboldTest, RemoveSameSymbol) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addSymbol('c'));
  EXPECT_TRUE(fa.addSymbol('d'));
  EXPECT_TRUE(fa.removeSymbol('c'));
  EXPECT_EQ(fa.countSymbols(),3u);
  EXPECT_FALSE(fa.removeSymbol('c'));
  
  
}
TEST(AutomatonRemoveSymboldTest, RemoveSymboleNotExist) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addSymbol('c'));
  EXPECT_TRUE(fa.addSymbol('d'));
  EXPECT_FALSE(fa.removeSymbol('z'));
}

TEST(AutomatonRemoveSymboldTest, RemoveSymboleWithTransition) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  fa.setStateFinal(1);
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_TRUE(fa.addTransition(1,'b',0));
  EXPECT_TRUE(fa.removeSymbol('b'));
  EXPECT_EQ(fa.countSymbols(),1u);
  EXPECT_EQ(fa.countTransitions(),1u);
  
 
}

TEST(AutomatonRemoveStateTest, RemoveOneState){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_EQ(fa.countStates(),3u);
  EXPECT_TRUE(fa.removeState(1));
  EXPECT_EQ(fa.countStates(),2u);
}
TEST(AutomatonRemoveStateTest, RemoveManyState){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_EQ(fa.countStates(),3u);
  EXPECT_TRUE(fa.removeState(1));
  EXPECT_EQ(fa.countStates(),2u);
  EXPECT_TRUE(fa.removeState(0));
  EXPECT_EQ(fa.countStates(),1u);
}
TEST(AutomatonRemoveStateTest, RemoveStateNotExist){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_EQ(fa.countStates(),3u);
  EXPECT_FALSE(fa.removeState(4));
}
TEST(AutomatonRemoveStateTest, RemoveBeginTransition){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.removeState(0));
  EXPECT_EQ(fa.countTransitions(),1u);
}
TEST(AutomatonRemoveStateTest, RemoveEndTransition){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'b',0));
  EXPECT_TRUE(fa.removeState(0));
  EXPECT_EQ(fa.countTransitions(),1u);
}


TEST(AutomatonInitialTest, InitialState){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
}
TEST(AutomatonInitialTest, IsNotAInitialState){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  fa.setStateInitial(0);
  EXPECT_FALSE(fa.isStateInitial(1));
}


TEST(AutomatonFinalTest, FinalState){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  fa.setStateFinal(0);
  EXPECT_TRUE(fa.isStateFinal(0));
}
TEST(AutomatonFinalTest, IsNotAFinalState){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  fa.setStateFinal(0);
  EXPECT_FALSE(fa.isStateFinal(1));
}

TEST(AutomatonInitialAndFinalTest, BothTest){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  fa.setStateFinal(0);
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateFinal(0));
  EXPECT_TRUE(fa.isStateInitial(0));
}


TEST(AutomatonTransitionTest, AddTransition){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_TRUE(fa.hasTransition(0,'a',1));
  EXPECT_EQ(fa.countTransitions(),1u);

}

TEST(AutomatonTransitionTest, RemoveTransition){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_EQ(fa.countTransitions(),1u);
  EXPECT_TRUE(fa.removeTransition(0,'a',1));
  EXPECT_EQ(fa.countTransitions(),0u);
}

TEST(AutomatonTransitionTest, RemoveTransitionNotExisting){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_EQ(fa.countTransitions(),0u);
  EXPECT_FALSE(fa.removeTransition(0,'a',1));

}

TEST(AutomatonTransitionTest, AddEpsilonTransition){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addTransition(0,fa::Epsilon,1));
  EXPECT_TRUE(fa.hasTransition(0,fa::Epsilon,1));

}

TEST(prettyPrintTest, print){
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.setStateInitial(0);
  fa.setStateInitial(1);
  fa.setStateFinal(1);
  fa.setStateFinal(4);
  fa.addTransition(0,'a',1);
  fa.addTransition(0,'a',2);
  fa.addTransition(0,'a',3);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);
  fa.addTransition(2,'b',4);
  fa.addTransition(3,'a',3);
  fa.addTransition(3,'b',4);
  fa.addTransition(4,'a',4);
  fa.prettyPrint(std::cout);
}

TEST(AutomatonEpsilonTest,hasEpsilonTransition){
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol(fa::Epsilon);
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.addTransition(0,fa::Epsilon,1));
  EXPECT_TRUE(fa.hasEpsilonTransition());
}
TEST(AutomatonEpsilonTest,DontHaveEpsilonTransition){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_FALSE(fa.hasEpsilonTransition());
}
TEST(AutomatonEpsilonTest,Twice){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.addTransition(0,fa::Epsilon,1));
  EXPECT_FALSE(fa.addTransition(0,fa::Epsilon,1));
  EXPECT_TRUE(fa.hasEpsilonTransition());
}
TEST(AutomatonEpsilonTest, ManyEspilonTransition){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addState(0));
  fa.setStateInitial(0);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addTransition(0,fa::Epsilon,1));
  EXPECT_TRUE(fa.addTransition(0,fa::Epsilon,2));
  EXPECT_TRUE(fa.addTransition(0,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'a',1));
  EXPECT_TRUE(fa.addTransition(3,fa::Epsilon,0));
  EXPECT_TRUE(fa.hasEpsilonTransition());
}

TEST(AutomatonEpsilonTest,RemoveEpsilon){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.addTransition(0,fa::Epsilon,1));
  EXPECT_TRUE(fa.hasEpsilonTransition());
  EXPECT_TRUE(fa.removeTransition(0,fa::Epsilon,1));
  EXPECT_FALSE(fa.hasEpsilonTransition());
}


TEST(AutomatonisDeterministic, Pierre_Cyrille_Heam_1){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  fa.setStateInitial(1);
  fa.setStateInitial(2);
  fa.setStateFinal(3);
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(1,'b',3));
  EXPECT_TRUE(fa.addTransition(2,'b',3));
  EXPECT_FALSE(fa.isDeterministic());
}

TEST(AutomatonisDeterministic, Pierre_Cyrille_Heam_2){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  fa.setStateFinal(3);
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(1,'b',3));
  EXPECT_TRUE(fa.addTransition(2,'b',3));
  EXPECT_FALSE(fa.isDeterministic());
}

TEST(AutomatonisDeterministic, Pierre_Cyrille_Heam_3){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(1,'a',1));
  EXPECT_TRUE(fa.addTransition(1,'b',3));
  EXPECT_TRUE(fa.addTransition(2,'b',3));
  EXPECT_FALSE(fa.isDeterministic());
}

TEST(AutomatonisDeterministic, Pierre_Cyrille_Heam_4){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(1,'b',3));
  EXPECT_TRUE(fa.addTransition(2,'b',3));
  EXPECT_TRUE(fa.addTransition(2,'a',2));
  EXPECT_TRUE(fa.isDeterministic());
}

TEST(AutomatonisComplete, CompleteAutomate){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addTransition(0,'b',1));
  EXPECT_TRUE(fa.addTransition(1,'b',0));
  EXPECT_TRUE(fa.addTransition(1,'a',1));
  EXPECT_TRUE(fa.addTransition(0,'a',0));

  EXPECT_TRUE(fa.isComplete());

}


TEST(AutomatonisComplete, NonCompleteAutomateNeedTransitions){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addSymbol('c'));
  EXPECT_TRUE(fa.addTransition(0,'b',1));
  EXPECT_TRUE(fa.addTransition(1,'b',0));
  EXPECT_TRUE(fa.addTransition(1,'a',1));
  EXPECT_TRUE(fa.addTransition(0,'a',0));

  EXPECT_FALSE(fa.isComplete());

}
TEST(AutomatonisComplete, CompleteAutomateWith2TransitionForASymbol){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_TRUE(fa.addTransition(0,'b',1));
  EXPECT_TRUE(fa.addTransition(1,'b',0));
  EXPECT_TRUE(fa.addTransition(1,'a',1));
  EXPECT_TRUE(fa.addTransition(0,'a',0));

  EXPECT_TRUE(fa.isComplete());

}

TEST(AutomatonCreateComplete, NonCompleteAutomate){
  fa::Automaton fa;
  fa::Automaton fb;

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_TRUE(fa.addTransition(0,'b',1));
  EXPECT_TRUE(fa.addTransition(1,'b',1));
  EXPECT_TRUE(fa.addTransition(0,'a',0));
  EXPECT_FALSE(fa.isComplete());
  fb=fa::Automaton::createComplete(fa);
  EXPECT_TRUE(fb.isComplete());
  EXPECT_TRUE(fb.hasSymbol('a'));
  EXPECT_TRUE(fb.hasSymbol('b'));
  EXPECT_EQ(fb.countSymbols(),2u);
  
}

TEST(AutomatonCreateComplete, CompleteAutomate){
  fa::Automaton fa;
  fa::Automaton fb;

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_TRUE(fa.addTransition(0,'a',0));
  EXPECT_TRUE(fa.addTransition(0,'b',2));
  EXPECT_TRUE(fa.addTransition(1,'b',1));
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'b',2));
  EXPECT_TRUE(fa.isComplete());
  fb=fa::Automaton::createComplete(fa);
  EXPECT_TRUE(fb.isComplete());
  EXPECT_TRUE(fb.hasSymbol('a'));
  EXPECT_TRUE(fb.hasSymbol('b'));
  EXPECT_EQ(fb.countSymbols(),2u);
  
}


TEST(AutomatonCreateComplement, ComplementAutomate){
  fa::Automaton fa;
  fa::Automaton fb;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.addTransition(0,'a',0));
  EXPECT_TRUE(fa.addTransition(0,'b',1));
  EXPECT_TRUE(fa.addTransition(1,'b',1));
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'b',2));
  fa.prettyPrint(std::cout);
  fb=fa::Automaton::createComplement(fa);
  fb.prettyPrint(std::cout);
  EXPECT_TRUE(fb.hasSymbol('a'));
  EXPECT_TRUE(fb.hasSymbol('b'));
  EXPECT_EQ(fb.countSymbols(),2u);

  //PEUT ETRE RAJOUTER VERIF
  
}

TEST(AutomatonCreateMirror, MirrorAutomate){
  fa::Automaton fa;
  fa::Automaton fb;

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  fa.setStateInitial(0);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_TRUE(fa.addTransition(0,'b',1));
  EXPECT_TRUE(fa.addTransition(1,'b',2));
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'b',0));
  EXPECT_TRUE(fa.addTransition(2,'a',0));
  fb=fa::Automaton::createMirror(fa);

  /*
  LES ETATS PEUVENT AVOIR CHANGER DE NOM

  EXPECT_TRUE(fb.isStateFinal(0));
  EXPECT_FALSE(fb.isStateFinal(2));
  EXPECT_TRUE(fb.isStateInitial(2));
  EXPECT_FALSE(fb.isStateInitial(0));

  EXPECT_TRUE(fb.hasTransition(1,'a',0));
  EXPECT_TRUE(fb.hasTransition(1,'b',0));
  EXPECT_TRUE(fb.hasTransition(2,'b',1));
  EXPECT_TRUE(fb.hasTransition(2,'a',1));
  EXPECT_TRUE(fb.hasTransition(0,'b',2));
  EXPECT_TRUE(fb.hasTransition(0,'a',2));*/
  
}

TEST(AutomatonIsLanguageEmpty, NotEmpty){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  fa.setStateInitial(0);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_TRUE(fa.addTransition(0,'b',1));
  EXPECT_TRUE(fa.addTransition(1,'b',2));
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'b',0));
  EXPECT_TRUE(fa.addTransition(2,'a',0));
  EXPECT_FALSE(fa.isLanguageEmpty());

}

TEST(AutomatonIsLanguageEmpty, UnitLanguage){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addSymbol('a'));
  fa.setStateInitial(0);
  fa.setStateFinal(0);
  EXPECT_FALSE(fa.isLanguageEmpty());
}
TEST(AutomatonIsLanguageEmpty, NotFinalState){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_TRUE(fa.addTransition(0,'b',1));
  EXPECT_TRUE(fa.addTransition(1,'b',2));
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'b',0));
  EXPECT_TRUE(fa.addTransition(2,'a',0));
  EXPECT_TRUE(fa.isLanguageEmpty());

}

TEST(AutomatonremoveNonAccessibleStates, OneState){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(18));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  fa.setStateInitial(0);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_TRUE(fa.addTransition(1,'b',2));
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'b',0));
  EXPECT_TRUE(fa.addTransition(2,'a',2));
  EXPECT_TRUE(fa.addTransition(18,'a',2));
  fa.removeNonAccessibleStates();
  EXPECT_EQ(fa.countStates(),3u);
}

TEST(AutomatonremoveNonAccessibleStates, NoInitialState){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(18));
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_TRUE(fa.addTransition(1,'b',2));
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'b',0));
  EXPECT_TRUE(fa.addTransition(2,'a',2));
  EXPECT_TRUE(fa.addTransition(18,'a',2));
  fa.removeNonAccessibleStates();
  EXPECT_TRUE(fa.isValid());
}


TEST(AutomatonremoveNonCoAccessibleStates, OneState){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  fa.setStateFinal(1);
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_TRUE(fa.addTransition(1,'a',0));
  EXPECT_TRUE(fa.addTransition(0,'a',3));
  EXPECT_TRUE(fa.addTransition(2,'b',1));
  fa.removeNonCoAccessibleStates();
  EXPECT_EQ(fa.countStates(),3u);
  EXPECT_TRUE(fa.isValid());

}

TEST(AutomatonremoveNonCoAccessibleStates, NoFinalState){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_TRUE(fa.addTransition(1,'a',0));
  EXPECT_TRUE(fa.addTransition(0,'a',3));
  EXPECT_TRUE(fa.addTransition(2,'b',1));
  fa.removeNonCoAccessibleStates();
  EXPECT_TRUE(fa.isValid());
}

TEST(AutomatonReadString, DessinJube){
  fa::Automaton fa;
  std::set<int> res;
  std::set<int> expected;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_TRUE(fa.addTransition(1,'b',1));
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'a',2));
  EXPECT_TRUE(fa.addTransition(0,'a',2));

  res=fa.readString("");
  expected.insert(0);
  EXPECT_EQ(expected,res);
  expected.clear();
  res.clear();

  res=fa.readString("a");
  expected.insert(1);
  expected.insert(2);
  EXPECT_EQ(expected,res);
  expected.clear();
  res.clear();

  res=fa.readString("aa");
  expected.insert(2);
  EXPECT_EQ(expected,res);
  expected.clear();
  res.clear();

  res=fa.readString("ab");
  expected.insert(1);
  EXPECT_EQ(expected,res);
  expected.clear();
  res.clear();

  res=fa.readString("b");
  EXPECT_EQ(expected,res);

}
TEST(AutomatonReadString, noreccursiviti){
  fa::Automaton fa;
  std::set<int> res;
  std::set<int> expected;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  fa.setStateInitial(0);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(0,'a',0));
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_TRUE(fa.addTransition(1,'a',0));
  EXPECT_TRUE(fa.addTransition(1,'a',1));
  EXPECT_TRUE(fa.addTransition(1,'b',2));
  expected.insert(0);
  expected.insert(1);
  res=fa.readString("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  EXPECT_EQ(expected,res);

}



TEST(AutomatonMatch, DessinJube){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_TRUE(fa.addTransition(1,'b',1));
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'a',2));
  EXPECT_TRUE(fa.addTransition(0,'a',2));

  EXPECT_FALSE(fa.match("aa"));

}

TEST(AutomatonMatch, DessinJubeWithFinalState){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  fa.setStateInitial(0);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_TRUE(fa.addTransition(1,'b',1));
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'a',2));
  EXPECT_TRUE(fa.addTransition(0,'a',2));

  EXPECT_TRUE(fa.match("aa"));

}

TEST(AutomatonhasEmptyIntersectionWith, NotEmptyIntersection){
  fa::Automaton fa;
  fa::Automaton fb;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  fa.setStateInitial(0);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_TRUE(fa.addTransition(1,'b',1));
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'a',2));
  EXPECT_TRUE(fa.addTransition(0,'a',2));

  EXPECT_TRUE(fb.addSymbol('a'));
  EXPECT_TRUE(fb.addSymbol('b'));
  EXPECT_TRUE(fb.addState(0));
  EXPECT_TRUE(fb.addState(1));
  EXPECT_TRUE(fb.addState(2));
  fb.setStateInitial(0);
  fb.setStateFinal(2);
  EXPECT_TRUE(fb.addTransition(0,'a',1));
  EXPECT_TRUE(fb.addTransition(1,'b',1));
  EXPECT_TRUE(fb.addTransition(1,'a',2));
  EXPECT_TRUE(fb.addTransition(2,'a',2));
  EXPECT_TRUE(fb.addTransition(0,'a',2));

  EXPECT_FALSE(fa.hasEmptyIntersectionWith(fb));

}

TEST(AutomatonhasEmptyIntersectionWith, emptyIntersection){
  fa::Automaton fa;
  fa::Automaton fb;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  fa.setStateInitial(0);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_TRUE(fa.addTransition(1,'b',1));
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'a',2));
  EXPECT_TRUE(fa.addTransition(0,'a',2));

  EXPECT_TRUE(fb.addSymbol('c'));
  EXPECT_TRUE(fb.addSymbol('d'));
  EXPECT_TRUE(fb.addState(0));
  EXPECT_TRUE(fb.addState(1));
  EXPECT_TRUE(fb.addState(2));
  fb.setStateInitial(0);
  fb.setStateFinal(2);
  EXPECT_TRUE(fb.addTransition(0,'c',1));
  EXPECT_TRUE(fb.addTransition(1,'d',1));
  EXPECT_TRUE(fb.addTransition(1,'c',2));
  EXPECT_TRUE(fb.addTransition(2,'c',2));
  EXPECT_TRUE(fb.addTransition(0,'d',2));

  EXPECT_TRUE(fa.hasEmptyIntersectionWith(fb));

}

TEST(AutomatoncreateDeterministic, DS2021){
  fa::Automaton fa;
  fa::Automaton fb;
  
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  EXPECT_TRUE(fa.addState(5));
  fa.setStateFinal(2);
  fa.setStateInitial(0);
  fa.setStateInitial(5);
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_TRUE(fa.addTransition(0,'a',3));
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(1,'a',4));
  EXPECT_TRUE(fa.addTransition(2,'b',5));
  EXPECT_TRUE(fa.addTransition(3,'b',1));
  EXPECT_TRUE(fa.addTransition(3,'a',4));
  EXPECT_TRUE(fa.addTransition(4,'b',2));
  EXPECT_TRUE(fa.addTransition(5,'b',4));
  EXPECT_TRUE(fa.addTransition(5,'a',2));

  fb = fb.createDeterministic(fa);
  EXPECT_TRUE(fb.isDeterministic());
  EXPECT_TRUE(fb.match("aa"));
  EXPECT_TRUE(fb.match("aab"));
  EXPECT_TRUE(fb.match("bb"));
  EXPECT_FALSE(fb.match("b"));
}

TEST(AutomatoncreateDeterministic, AlreadyDeterlinistic){
  fa::Automaton fa;
  fa::Automaton fb;
  
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  fa.setStateFinal(2);
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.addTransition(0,'a',1));
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'b',0));
  EXPECT_TRUE(fa.isDeterministic());
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("aabaa"));
  EXPECT_FALSE(fa.match("ab"));

  fb = fa::Automaton::createDeterministic(fa);
  EXPECT_TRUE(fb.isDeterministic());
  EXPECT_TRUE(fb.match("aa"));
  EXPECT_TRUE(fb.match("aabaa"));
  EXPECT_FALSE(fb.match("ab"));

}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}