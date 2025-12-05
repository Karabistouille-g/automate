#include "Automaton.h"
#include <iostream>
#include <limits>
#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>

using namespace std;

namespace fa {

  Automaton::Automaton() {
  }

  bool Automaton::isValid() const {
    if (alphabet.empty()) return false;
    if (states.empty()) return false;
    return true;
  }

  bool Automaton::addSymbol(char symbol) {
    if (!isgraph(symbol)) return false;
    if (hasSymbol(symbol)) return false;
    alphabet.insert(symbol);
    return true;
  }

  bool Automaton::removeSymbol(char symbol) {
    if (!hasSymbol(symbol)) return false;

    for (auto [state, mapChar] : transitions) {
        mapChar.erase(symbol);
    }
    
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
    if (state < 0) return false;
    if (hasState(state)) return false;
    states.insert({state, NONE});
    return true;
  }

  bool Automaton::removeState(int state) {
    if (!hasState(state)) return false;
    
    transitions.erase(state);

    for (auto [src, mapChar] : transitions) {
      for (auto [alpha, dest] : mapChar) {
        dest.erase(state);
      }
    }

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
    if (!hasState(from)) return false;
    if (!hasState(to)) return false;
    if (!hasSymbol(alpha) && alpha != fa::Epsilon) return false;
    if (hasTransition(from, alpha, to)) return false;

    transitions[from][alpha].insert(to);
    return true;
  }

  bool Automaton::removeTransition(int from, char alpha, int to) {
    auto itState = transitions.find(from);
    if (itState == transitions.end()) return false;

    auto itChar = itState->second.find(alpha);
    if (itChar == itState->second.end()) return false;

    bool removed = itChar->second.erase(to) > 0;
    
    if (itChar->second.empty()) {
        itState->second.erase(itChar);
    }
    
    if (itState->second.empty()) {
        transitions.erase(itState);
    }

    return removed;
  }

  bool Automaton::hasTransition(int from, char alpha, int to) const {
    auto itState = transitions.find(from);
    if (itState == transitions.end()) return false;

    auto itChar = itState->second.find(alpha);
    if (itChar == itState->second.end()) return false;

    return itChar->second.count(to) == 1;
  }

  std::size_t Automaton::countTransitions() const {
    std::size_t count = 0;
    for (const auto& [state, mapChar] : transitions) {
        for (const auto& [alpha, dests] : mapChar) {
            count += dests.size();
        }
    }
    return count;
  }

  void Automaton::prettyPrint(std::ostream& os) const {
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
      
      auto itTrans = transitions.find(state.first);
      if (itTrans != transitions.end()) {
          for (auto c : alphabet) {
            if (itTrans->second.count(c)) {
                os << "  For letter " << c << ": ";
                for (int dest : itTrans->second.at(c)) {
                    os << dest << " ";
                }
                os << std::endl;
            }
          }
          if (itTrans->second.count(fa::Epsilon)) {
             os << "  For letter Epsilon: ";
             for (int dest : itTrans->second.at(fa::Epsilon)) {
                 os << dest << " ";
             }
             os << std::endl;
          }
      }
    }
  }

  bool Automaton::hasEpsilonTransition() const {
    for (const auto [state, mapChar] : transitions) {
      if (mapChar.count(fa::Epsilon) > 0 && !mapChar.at(fa::Epsilon).empty())
        return true;
    }
    return false;
  }

  bool Automaton::isDeterministic() const {
    if (hasEpsilonTransition()) return false;

    int cpt = 0;
    for (auto state : states) {
      if (isStateInitial(state.first)) {
        cpt++;
      }
    }
    if (cpt != 1) return false;

    for (const auto& [state, mapChar] : transitions) {
        for (const auto& [alpha, dests] : mapChar) {
            if (dests.size() > 1) return false;
        }
    }
    return true;
  }

  bool Automaton::isComplete() const {
    for (auto state : states) {
      auto itTrans = transitions.find(state.first);
      
      if (itTrans == transitions.end()) {
          if (!alphabet.empty()) return false;
          continue;
      }

      for (char c : alphabet) {
          if (itTrans->second.find(c) == itTrans->second.end() || 
              itTrans->second.at(c).empty()) {
              return false;
          }
      }
    }
    return true;
  }

  Automaton Automaton::createComplete(const Automaton& automaton) {
    if (automaton.isComplete()) return automaton;

    Automaton comp = automaton;
    int newState = 0;
    while (comp.hasState(newState)) {
      newState++;
    }
    comp.addState(newState);

    for (auto c : comp.alphabet) {
        comp.addTransition(newState, c, newState);
    }


    for (auto s : comp.states) {
        for (auto c : comp.alphabet) {
             if (!comp.hasTransition(s.first, c, newState) &&
                 (!comp.transitions.count(s.first) || 
                  !comp.transitions.at(s.first).count(c) ||
                  comp.transitions.at(s.first).at(c).empty())) 
             {
                 comp.addTransition(s.first, c, newState);
             }
        }
    }

    return comp;
  }

  Automaton Automaton::createComplement(const Automaton& automaton) {
    Automaton res = createDeterministic(automaton);
    res = createComplete(res);

    for (auto s : res.states) {
      int state = s.first;
      if (res.isStateFinal(state)) {
        if (res.states[state] == BOTH) res.states[state] = INITIAL;
        else res.states[state] = NONE;
      } else {
        if (res.states[state] == INITIAL) res.states[state] = BOTH;
        else res.states[state] = FINAL;
      }
    }
    return res;
  }

  Automaton Automaton::createMirror(const Automaton& automaton) {
    Automaton mirror;
    mirror.alphabet = automaton.alphabet;

    for (auto state : automaton.states) {
      mirror.addState(state.first);
      if (automaton.isStateInitial(state.first)) {
        mirror.setStateFinal(state.first);
      }
      if (automaton.isStateFinal(state.first)) {
        mirror.setStateInitial(state.first);
      }
    }

    for (const auto& [from, mapChar] : automaton.transitions) {
        for (const auto& [alpha, dests] : mapChar) {
            for (int to : dests) {
                mirror.addTransition(to, alpha, from);
            }
        }
    }

    return mirror;
  }

  std::set<int> Automaton::makeTransition(const std::set<int>& origin, char alpha) const {
    std::set<int> result;
    if (!hasSymbol(alpha)) return result;
    for (auto from : origin) {
        auto itState = transitions.find(from);
        if (itState != transitions.end()) {
            auto itChar = itState->second.find(alpha);
            if (itChar != itState->second.end()) {
                result.insert(itChar->second.begin(), itChar->second.end());
            }
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
    for (auto state : match) {
      if (isStateFinal(state)) return true;
    }
    return false;
  }

  bool Automaton::isLanguageEmpty() const {
    // Construction du graphe (voisin) plus rapide
    std::unordered_map<int, std::vector<int>> voisin;
    
    for (const auto& [from, mapChar] : transitions) {
        for (const auto& [alpha, dests] : mapChar) {
            for (int to : dests) {
                voisin[from].push_back(to);
            }
        }
    }

    std::vector<int> stack;
    std::set<int> visited;


    for (auto t : states) {
      int s = t.first;
      if (isStateInitial(s)) {
          if (isStateFinal(s)) return false;
          stack.push_back(s);
          visited.insert(s);
      } 
    }

    while (!stack.empty()) {
      int state = stack.back();
      stack.pop_back();

      if (isStateFinal(state)) {
        return false;
      }

      if (voisin.count(state)) {
          for (int next : voisin[state]) {
            if (visited.find(next) == visited.end()) {
              stack.push_back(next);
              visited.insert(next);
            }
          }
      }
    }

    return true;
  }

  void Automaton::removeNonAccessibleStates() {
    std::vector<int> queue;
    std::set<int> visited;

    bool initial = false;
    for (auto s : states) {
      if (isStateInitial(s.first)) {
          queue.push_back(s.first);
          visited.insert(s.first);
          initial = true;
      }
    }

    if (!initial) {
        states.clear();
        transitions.clear();
        return;
    }

    while (!queue.empty()) {
      int state = queue.back();
      queue.pop_back();
      auto itTrans = transitions.find(state);
      if (itTrans != transitions.end()) {
          for (auto& [alpha, dests] : itTrans->second) {
              for (int next : dests) {
                  if (visited.find(next) == visited.end()) {
                      queue.push_back(next);
                      visited.insert(next);
                  }
              }
          }
      }
    }
    
    std::vector<int> remove;
    for (auto current : states) {
      if (visited.find(current.first) == visited.end()) {
        remove.push_back(current.first);
      }
    }
    for (auto rm : remove) {
      removeState(rm);
    }
  } 

  void Automaton::removeNonCoAccessibleStates() {
    std::vector<int> queue;
    std::set<int> visited;

    bool final = false;
    for (auto s : states) {
      if (isStateFinal(s.first)) {
          queue.push_back(s.first);
          visited.insert(s.first);
          final = true;
      }
    }

    if (!final) {
        states.clear();
        transitions.clear();
        return;
    }

    std::unordered_map<int, std::vector<int>> predecessors;
    for (const auto& [from, mapChar] : transitions) {
        for (const auto& [alpha, dests] : mapChar) {
            for (int to : dests) {
                predecessors[to].push_back(from);
            }
        }
    }

    while (!queue.empty()) {
      int state = queue.back();
      queue.pop_back();
      
      if (predecessors.count(state)) {
          for (int prev : predecessors[state]) {
            if (visited.find(prev) == visited.end()) {
                queue.push_back(prev);
                visited.insert(prev);
            }
          }
      }
    }

    std::vector<int> remove;
    for (auto current : states) {
      if (visited.find(current.first) == visited.end()) {
        remove.push_back(current.first);
      }
    }

    for (auto rm : remove) {
      removeState(rm);
    }
  }

  bool Automaton::hasEmptyIntersectionWith(const Automaton& other) const {
    Automaton intersection = Automaton::createIntersection(*this, other);
    return intersection.isLanguageEmpty();
  }

  bool Automaton::isIncludedIn(const Automaton& other) const {
    Automaton complement = Automaton::createComplement(other);
    Automaton intersection = Automaton::createIntersection(*this, complement);
    return intersection.isLanguageEmpty();
  }

  Automaton Automaton::createIntersection(const Automaton& lhs, const Automaton& rhs) {
    Automaton first = lhs;
    Automaton second = rhs;
    Automaton final;

    std::set_intersection(
      first.alphabet.begin(), first.alphabet.end(),
      second.alphabet.begin(), second.alphabet.end(),
      std::inserter(final.alphabet, final.alphabet.begin())
    );

    int firstInitial = -1;
    int secondInitial = -1;

    for (auto s : first.states) {
      if (first.isStateInitial(s.first)) {
        firstInitial = s.first;
        break;
      }
    }
    for (auto s : second.states) {
      if (second.isStateInitial(s.first)) {
        secondInitial = s.first;
        break;
      }
    }

    if (firstInitial == -1 || secondInitial == -1) {
      return final;
    }

    int cpt = 0;
    std::map<std::pair<int, int>, int> translate;
    std::deque<std::pair<int, int>> queue;
    std::pair<int, int> initial = {firstInitial, secondInitial};
    translate[initial] = cpt;

    final.addState(cpt);
    final.setStateInitial(cpt);
    if (first.isStateFinal(firstInitial) && second.isStateFinal(secondInitial)) {
      final.setStateFinal(cpt);
    }
    queue.push_back(initial);
    cpt++;

    while (!queue.empty()) {
      std::pair<int, int> current = queue.front();
      queue.pop_front();

      int stateA = current.first;
      int stateB = current.second;
      int newStart = translate[current];

      for (char c : final.alphabet) {
        std::set<int> nextStateA = first.makeTransition({stateA}, c);
        if (nextStateA.empty()) continue;
        int newStateA = *nextStateA.begin();

        std::set<int> nextStateB = second.makeTransition({stateB}, c);
        if (nextStateB.empty()) continue;
        int newStateB = *nextStateB.begin();

        std::pair<int, int> newCouple = {newStateA, newStateB};

        if (translate.find(newCouple) == translate.end()) {
          translate[newCouple] = cpt;
          final.addState(cpt);

          if (first.isStateFinal(newStateA) && second.isStateFinal(newStateB)) final.setStateFinal(cpt);
          
          queue.push_back(newCouple);
          cpt++;
        }

        int newTarget = translate[newCouple];
        final.addTransition(newStart, c, newTarget);
      }
    }
    return final;
  }

  Automaton Automaton::createDeterministic(const Automaton& other) {
    if (other.isDeterministic()) return other;

    Automaton fa;
    fa.alphabet = other.alphabet;

    std::set<int> startSet;
    for (auto s : other.states) {
      if (other.isStateInitial(s.first)) {
        startSet.insert(s.first);
      }
    }

    std::map<std::set<int>, int> translate;
    std::deque<std::set<int>> queue;

    int cpt = 0;
    translate[startSet] = cpt;
    fa.addState(cpt);
    fa.setStateInitial(cpt);
    queue.push_back(startSet);

    bool startIsFinal = false;
    for (auto s : startSet) {
      if (other.isStateFinal(s)) {
        startIsFinal = true;
        break;
      }
    }
    if (startIsFinal) {
      fa.setStateFinal(cpt);
    }
    cpt++;

    while (!queue.empty()) {
      std::set<int> currentSet = queue.front();
      queue.pop_front();
      
      int currentState = translate[currentSet];

      for (char alpha : fa.alphabet) {
        std::set<int> nextSet = other.makeTransition(currentSet, alpha);

        if (nextSet.empty()) continue;

        if (translate.find(nextSet) == translate.end()) {
          translate[nextSet] = cpt;
          fa.addState(cpt);

          bool isFinal = false;
          for (auto s : nextSet) {
            if (other.isStateFinal(s)) {
              isFinal = true;
              break;
            }
          }
          if (isFinal) fa.setStateFinal(cpt);
          
          queue.push_back(nextSet);
          cpt++;
        }

        fa.addTransition(currentState, alpha, translate[nextSet]);
      }
    }
    
    return fa;
  }

  Automaton Automaton::createMinimalMoore(const Automaton& other) {
    // TODO
    return other;
  }

  Automaton Automaton::createMinimalBrzozowski(const Automaton& other) {
    // TODO
    return other;
  }
}