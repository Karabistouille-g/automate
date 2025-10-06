#include "Automaton.h"
#include <iostream>
using namespace std;


namespace fa {

    Automaton::Automaton() {
    }

  bool Automaton::isValid() const {
    if (alphabet.empty() || states.empty()) {
      return false;
    }
    return true;
  };

  bool Automaton::addSymbol(char symbol) {
    if (!isgraph(symbol) && symbol != fa::Epsilon) {
      return false;
    } else {
      alphabet.insert(symbol);
      return true;
    }
  }

  bool Automaton::removeSymbol(char symbol) {
    if (hasSymbol(symbol) || symbol == fa::Epsilon) {
      alphabet.erase(symbol);
      return true;
    } else {
      return false;
    }
  }

  bool Automaton::hasSymbol(char symbol) const {
    return alphabet.find(symbol) != alphabet.end();
  }

  std::size_t Automaton::countSymbols() const {
    return alphabet.size();
  }

  bool Automaton::addState(int state) {
    if (hasState(state)) {
      return false;
    } else {
      states.insert(state);
      return true;
    }
  }

  bool Automaton::removeState(int state) {
    if (hasState(state)) {
      states.erase(state);
      return true;
    } else {
      return false;
    }
  }

  bool Automaton::hasState(int state) const {
    return states.find(state) != states.end();
  }

  std::size_t Automaton::countStates() const {
    return states.size();
  }

  void Automaton::setStateInitial(int state) {
    if (initial.find(state) == initial.end() && hasState(state)) {
      initial.insert(state);
    }
  }

  bool Automaton::isStateInitial(int state) const {
    return initial.find(state) != initial.end();
  }

  void Automaton::setStateFinal(int state) {
    if (final.find(state) == final.end() && hasState(state)) {
      final.insert(state);
    }
  }

  bool Automaton::isStateFinal(int state) const {
    return final.find(state) != final.end();
  }

  bool Automaton::addTransition(int from, char alpha, int to) {
    if (hasTransition(from, alpha, to)) {
      return false;
    } else {
      transitions[from][alpha].insert(to);
      return true;
    }
  }

  bool Automaton::removeTransition(int from, char alpha, int to) {
    return transitions[from][alpha].erase(to) == 1;
  }

  bool Automaton::hasTransition(int from, char alpha, int to) const {
    if (transitions.find(from) == transitions.end()) {
      return false;
    } else if (transitions.at(from).find(alpha) == transitions.at(from).end()) {
      return false;
    } else if (transitions.at(from).at(alpha).count(to) > 0) {
      return true;
    } else {
      return false;
    }
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

