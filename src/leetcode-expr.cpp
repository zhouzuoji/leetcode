#include <string>
#include <stack>

using namespace std;

namespace leetcode {
	namespace expr {
		enum class NodeType { parenthese_open, parenthese_close, _operator, operand, call};
		enum class Operator {plus, substract, multiply, divide};
		typedef struct _Node {
			NodeType type;
			union {
				Operator _operator;
				int operand;
			};
			_Node() {} 
			_Node(NodeType type) : type(type) {}
			_Node(int _operand): type(NodeType::operand), operand(_operand) {}
			_Node(Operator __operator) : type(NodeType::_operator), _operator(__operator) {}
		} Node;
		
		char OperatorToStr(Operator _operator) {
			switch (_operator) {
			case Operator::plus: return '+';
			case Operator::substract: return '-';
			case Operator::multiply: return '*';
			case Operator::divide: return '/';
			default:
				return '\0';
			}
		}

		void dump_reverse_polish(stack<Node> stk) {
			while (!stk.empty()) {
				Node x = stk.top();
				stk.pop();
				if (x.type == NodeType::_operator)
					printf("%c\n", OperatorToStr(x._operator));
				else if (x.type==NodeType::operand)
					printf("%d\n", x.operand);
			}
		}

		int reverse_polish_compute(stack<Node>& stk1) {
			stack<Node> stk2;
			while (!stk1.empty()) {
				while (stk1.top().type == NodeType::_operator) {
					stk2.push(stk1.top());
					stk1.pop();
				}
				Node x, na, nb;
				if (stk2.empty())
					return stk1.top().operand;
				x = stk2.top();
				if (x.type == NodeType::operand) {
					nb = x;
					stk2.pop();
					na = stk1.top();
					stk1.pop();
					x = stk2.top();
					stk2.pop();
				}
				else {
					nb = stk1.top();
					stk1.pop();
					na = stk1.top();
					stk1.pop();
					if (na.type == NodeType::_operator) {					
						stk2.push(nb);
						stk2.push(na);
						continue;
					}
					stk2.pop();
				}
				
				int a = na.operand, b = nb.operand;
				switch (x._operator) {
				case Operator::plus:
					printf("%d + %d\n", a, b);
					a += b;
					break;
				case Operator::substract:
					printf("%d - %d\n", a, b);
					a -= b;
					break;
				case Operator::multiply:
					printf("%d * %d\n", a, b);
					a *= b;
					break;
				case Operator::divide:
					printf("%d / %d\n", a, b);
					a /= b;
					break;
				}
				stk1.push(a);
			}
			return 0;
		}

		// reverse_polish_notation
		stack<Node> make_reverse_polish(const string& s) {
			size_t n = s.size();
			stack<Node> stk1, stk2;
			size_t i = 0;
			while (i < n) {
				while (i < n && s[i] <= 32) ++i;
				if (i == n) break;
				//printf("start s[%d]: %c\n", i, s[i]);
				switch (s[i]) {
				case '(':
					stk2.emplace(NodeType::parenthese_open);
					break;
				case ')':
					stk2.pop();
					if (!stk2.empty()) {
						Node tmp = stk2.top();
						if (tmp.type != NodeType::parenthese_open) {
							printf("push operator %c\n", OperatorToStr(tmp._operator));
							stk1.push(tmp);
							stk2.pop();
						}
					}
					break;
				case '+':
					printf("pending operator %c\n", s[i]);
					stk2.emplace(Operator::plus);
					break;
				case '-':
					printf("pending operator %c\n", s[i]);
					stk2.emplace(Operator::substract);
					break;
				default:
				{
					int x = 0;
					while (i < n && isdigit(s[i])) {
						x = x * 10 + s[i] - '0';
						++i;
					}
					--i;
					printf("push operand %d\n", x);
					stk1.push(x);
					if (!stk2.empty()) {
						Node tmp=stk2.top();
						if (tmp.type != NodeType::parenthese_open) {
							printf("push operator %c\n", OperatorToStr(tmp._operator));
							stk1.push(tmp);
							stk2.pop();
						}
					}
				}
				}
				++i;
			}
			//printf("****************************\n");
			//dump_reverse_polish(stk1);
			return stk1;
		}

		void calc(stack<Node>& stk, Operator _operator) {
			int b = stk.top().operand;
			stk.pop();
			int a = stk.top().operand;
			stk.pop();
			switch (_operator) {
			case Operator::plus:
				printf("%d + %d\n", a, b);
				a += b;
				break;
			case Operator::substract:
				printf("%d - %d\n", a, b);
				a -= b;
				break;
			case Operator::multiply:
				printf("%d * %d\n", a, b);
				a *= b;
				break;
			case Operator::divide:
				printf("%d / %d\n", a, b);
				a /= b;
				break;
			}
			stk.push(a);
		}

		int eval(const string& s) {
			size_t n = s.size();
			stack<Node> stk1, stk2;
			size_t i = 0;
			while (i < n) {
				while (i < n && s[i] <= 32) ++i;
				if (i == n) break;
				//printf("start s[%d]: %c\n", i, s[i]);
				switch (s[i]) {
				case '(':
					stk2.emplace(NodeType::parenthese_open);
					break;
				case ')':
					stk2.pop();
					if (!stk2.empty()) {
						Node tmp = stk2.top();
						if (tmp.type != NodeType::parenthese_open) {
							stk2.pop();
							calc(stk1, tmp._operator);
						}
					}
					break;
				case '+':
					printf("pending operator %c\n", s[i]);
					stk2.emplace(Operator::plus);
					break;
				case '-':
					printf("pending operator %c\n", s[i]);
					stk2.emplace(Operator::substract);
					break;
				default:
				{
					int x = 0;
					while (i < n && isdigit(s[i])) {
						x = x * 10 + s[i] - '0';
						++i;
					}
					--i;
					printf("push operand %d\n", x);
					stk1.push(x);
					if (!stk2.empty()) {
						Node tmp = stk2.top();
						if (tmp.type != NodeType::parenthese_open) {
							printf("push operator %c\n", OperatorToStr(tmp._operator));
							stk2.pop();
							calc(stk1, tmp._operator);
						}
					}
				}
				}
				++i;
			}
			return stk1.top().operand;
		}
	}
} // namespace leetcode