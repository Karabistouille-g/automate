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
    if (!isgraph(symbol) && symbol != fa::Epsilon) return false;
    if (hasSymbol(symbol)) return false;
    alphabet.insert(symbol);
    return true;
  }

  bool Automaton::removeSymbol(char symbol) {
    if (!hasSymbol(symbol)) return false;
    alphabet.erase(symbol);
    return true;
  }

  bool Automaton::hasSymbol(char symbol) const {
    return alphabet.count(symbol) == 1;
  }

  std::size_t Automaton::countSymbols() const {
    return alphabet.size();
  }

  bool Automaton::addState(int state) {
    if (hasState(state)) return false;
    states.insert({state, NONE});
    return true;
  }

  bool Automaton::removeState(int state) {
    if (!hasState(state)) return false;
    states.erase(state);
    return true;
  }

  bool Automaton::hasState(int state) const {
    return states.count(state) == 1;
  }

  std::size_t Automaton::countStates() const {
    return states.size();
  }

  void Automaton::setStateInitial(int state) {
    if (!hasState(state)) return;
    if (isStateInitial(state)) return;
    if (isStateFinal(state)) {
      states[state] = BOTH;
      return;
    }
    states[state] = INITIAL;
  }

  bool Automaton::isStateInitial(int state) const {
    if (states.count(state) == 0) return false;
    return states.at(state) == INITIAL || states.at(state) == BOTH;
  }

  void Automaton::setStateFinal(int state) {
    if (!hasState(state)) return;
    if (isStateFinal(state)) return;
    if (isStateInitial(state)) {
      states[state] = BOTH;
      return;
    }
    states[state] = FINAL;
  }

  bool Automaton::isStateFinal(int state) const {
    if (states.count(state) == 0) return false;
    return states.at(state) == FINAL || states.at(state) == BOTH;
  }

  bool Automaton::addTransition(int from, char alpha, int to) {
    if (hasTransition(from, alpha, to)) return false;
    transitions.insert(std::make_tuple(from, alpha, to));
    return true;
  }

  bool Automaton::removeTransition(int from, char alpha, int to) {
    if (!hasTransition(from, alpha, to)) return false;
    transitions.erase(std::make_tuple(from, alpha, to));
    return true;
  }

  bool Automaton::hasTransition(int from, char alpha, int to) const {
    return transitions.count(std::make_tuple(from, alpha, to)) == 1;
  }

  std::size_t Automaton::countTransitions() const{
    return transitions.size();
  }

  void Automaton::prettyPrint(std::ostream& os) const{
    os << "Initial states : "<< std::endl;
    for (auto state : states) {
      if(isStateInitial(state.first)){
        os << state.first << " ";
      }
    }
    os << std::endl;
    os << "Final states : " << std::endl;
    for (auto state : states) {
      if(isStateFinal(state.first)){
        os << state.first << " ";
      }
    }
    os << std::endl;
    os << "Transitions:" << std::endl;
    for (auto state : states) {
      os << "For state " << state.first << ":" << std::endl;
      for (auto c : alphabet) {
        os << "  For letter " << c << ": ";
        for (const auto &i : transitions){
          if((state.first == std::get<0>(i)) && (c==std::get<1>(i))){
            os << std::get<2>(i) << " ";
          }
        }
        os << std::endl;
      }
    }
    return ;
  }

  bool Automaton::hasEpsilonTransition() const {
    if (!hasSymbol(fa::Epsilon)) return false;
    for (auto state : transitions) {
      if (std::get<1>(state) == (fa::Epsilon))
        return true;
    }
    return false;
  }

  bool Automaton::isDeterministic() const {
    for (auto current : transitions) {
      for (auto check : transitions) {
        if (check == current) continue;
        if (std::get<0>(current) == std::get<0>(check)) {
          if (std::get<1>(current) == std::get<1>(check)) {
            return false;
          }
        }
      }
    }
    return true;
  }

    bool Automaton::isComplete() const {
      for (const auto& state : states) {
        int s = state.first;
        for (char c : alphabet) {
          bool found = false;
          for (const auto& t : transitions) {
            if (std::get<0>(t) == s && std::get<1>(t) == c) {
              found = true;
              break;
            }
          }
          if (!found) return false;
        }
      }
      return true;
    }

  Automaton Automaton::createComplete(const Automaton& automaton) {
    if (automaton.isComplete()) return automaton;
    Automaton comp = automaton;
    auto it = std::prev(comp.states.end());
    int newState = it->first + 1;
    comp.addState(newState);
    for (char c : comp.alphabet) {
      comp.addTransition(newState, c, newState);
    }
    for (const auto& state : comp.states) {
        int s = state.first;
        for (char c : comp.alphabet) {
          bool found = false;
          for (const auto& t : comp.transitions) {
            if (std::get<0>(t) == s && std::get<1>(t) == c) {
              found = true;
              break;
            }
          }
          if (!found) comp.addTransition(s, c, newState);
        }
      }
    return comp;
  }

  Automaton Automaton::createComplement(const Automaton& automaton) {
    return automaton;
  }

  Automaton Automaton::createMirror(const Automaton& automaton) {
    Automaton mirror = automaton;

    std::set<int> tempInitial;
    for (auto state : mirror.states) {
      if(mirror.isStateInitial(state.first)){
        tempInitial.insert(state.first);
      }
    }

    std::set<int> tempFinal;
    for (auto state : mirror.states) {
      if(mirror.isStateFinal(state.first)){
        tempFinal.insert(state.first);
      }
    }

    for (auto state : tempInitial) {
      mirror.states[state] = INITIAL;
    }

    for (auto state : tempFinal) {
      if (mirror.states[state] == INITIAL) {
        mirror.states[state] = BOTH;
      } else {
        mirror.states[state] = FINAL;
      }
    }

    for (auto tuple : automaton.transitions) {
      mirror.addTransition(std::get<2>(tuple), std::get<1>(tuple), std::get<0>(tuple));
    }

    return mirror;
  }

  std::set<int> Automaton::makeTransition(const std::set<int>& origin, char alpha) const {
    std::set<int> result;
    for (auto from : origin) {
      for (auto current : states) {
        if (hasTransition(from, alpha, current.first))
          result.insert(current.first);
      }
    }
    return result;
  }

  std::set<int> Automaton::readString(const std::string& word) const {
    std::set<int> path;
    for (auto state : states) {
      if (state.second == INITIAL || state.second == BOTH) {
        path.insert(state.first);
      }
    }
    for (auto c : word) {
      path = makeTransition(path, c);
    }
    return path;
  }

  bool Automaton::match(const std::string& word) const {
    std::set<int> match = readString(word);
    bool stateInitial = false;
    bool stateFinal = false;
    for (auto state : match) {
      if (isStateInitial(state)) stateInitial = true;
      if (isStateFinal(state)) stateFinal = true;
    }
    if (!stateInitial || !stateFinal) return false;
    return true;
  }
}

