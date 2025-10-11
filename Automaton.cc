#include "Automaton.h"
#include <iostream>
using namespace std;


namespace fa {

    Automaton::Automaton() {
    }

  bool Automaton::isValid() const {
    if (alphabet.empty()) return false;
    if (states.empty()) return false;
    return true;
  };

  bool Automaton::addSymbol(char symbol) {
    if (!isgraph(symbol) || symbol == fa::Epsilon) return false;
    alphabet.push_back(symbol);
    return true;
  }

  bool Automaton::removeSymbol(char symbol) {
    if (!hasSymbol(symbol)) return false;
    alphabet.erase(std::find(alphabet.begin(), alphabet.end(), symbol));
    return true;
  }

  bool Automaton::hasSymbol(char symbol) const {
    auto sym = std::find(alphabet.begin(), alphabet.end(), symbol);
    return sym != alphabet.end();
  }

  std::size_t Automaton::countSymbols() const {
    return alphabet.size();
  }

  bool Automaton::addState(int state) {
    if (hasState(state)) return false;
    states.push_back(state);
    return true;
  }

  bool Automaton::removeState(int state) {
    if (!hasState(state)) return false;
    states.erase(std::find(states.begin(), states.end(), state));
    return true;
  }

  bool Automaton::hasState(int state) const {
    auto sta = std::find(states.begin(), states.end(), state);
    return sta != states.end();
  }

  std::size_t Automaton::countStates() const {
    return states.size();
  }

  void Automaton::setStateInitial(int state) {
    if (!hasState(state)) return;
    if (isStateInitial(state)) return;
    initial.push_back(state);
  }

  bool Automaton::isStateInitial(int state) const {
    auto sta = std::find(initial.begin(), initial.end(), state);
    return sta != initial.end();
  }

  void Automaton::setStateFinal(int state) {
    if (!hasState(state)) return;
    if (isStateFinal(state)) return;
    initial.push_back(state);
  }

  bool Automaton::isStateFinal(int state) const {
    auto sta = std::find(final.begin(), final.end(), state);
    return sta != final.end();
  }

  bool Automaton::addTransition(int from, char alpha, int to) {
    if (hasTransition(from, alpha, to)) return false;
    transitions[from][alpha].push_back(to);
    return true;
  }

  bool Automaton::removeTransition(int from, char alpha, int to) {
    if (!hasTransition(from, alpha, to)) return false;
    auto &trans = transitions[from][alpha];
    trans.erase(std::find(trans.begin(), trans.end(), to));
    return true;
  }

  bool Automaton::hasTransition(int from, char alpha, int to) const {
    if (std::find(transitions.begin(), transitions.end(), from) != transitions.end()) return false;
    auto transChar = transitions.at(from);
    if (std::find(transChar.begin(), transChar.end(), alpha) != transChar.end()) return false;
    auto transInt = transitions.at(from).at(alpha);
    if (std::find(transInt.begin(), transInt.end(), to) != transInt.end()) return false;
    return true;
  }

  std::size_t Automaton::countTransitions() const{
    std::size_t total = 0;
    for (auto &pairFrom : transitions) {
        for (auto &pairAlpha : pairFrom.second) {
            total += pairAlpha.second.size();
        }
    }
    return total;
  }

  
}

