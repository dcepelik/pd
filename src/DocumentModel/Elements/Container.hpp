#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Element.hpp"

using namespace BoxModel;
using namespace DocumentModel;
using namespace DocumentModel::Elements;
using namespace std;


namespace DocumentModel
{
	namespace Elements
	{
		class Container : public Element
		{
		protected:
			string name;
			vector<shared_ptr<Element>> children;


			virtual void prerender(vector<shared_ptr<Box>> &boxes)
			{
				(void) boxes;
			}


			virtual void postrender(vector<shared_ptr<Box>> &boxes)
			{
				(void) boxes;
			}


		public:
			Container(shared_ptr<Element> parent, string name)
				: Element(parent, name)
			{
			}


			void addChild(shared_ptr<Element> child)
			{
				children.push_back(shared_ptr<Element>(move(child)));
			}


			virtual void getChildrenRecursive(vector<shared_ptr<Element>> &children)
			{
				for (auto child: this->children) {
					children.push_back(child);
					child->getChildrenRecursive(children);
				}
			}


			virtual string getTextualContent()
			{
				/* TODO don't be so wasteful, use a string builder instead! */

				string str;
				for (auto child: children) {
					str += child->getTextualContent();
				}

				return str;
			}


			virtual void render(vector<shared_ptr<Box>> &boxes)
			{
				prerender(boxes);
				for (auto it = children.begin(); it != children.end(); it++)
					(*it)->render(boxes);
				postrender(boxes);
			}


			virtual void dump(int level)
			{	
				Element::dump(level);

				for (auto elem = children.begin(); elem != children.end(); elem++) {
					(*elem)->dump(level + 1);
				}
			}


			virtual void removeEmptyChildren()
			{
				auto it = children.begin();

				while (it != children.end()) {
					if ((*it)->empty()) {
						it = children.erase(it);
					}
					else {
						(*it)->removeEmptyChildren();
						it++;
					}
				}
			}


			virtual bool empty()
			{
				for (auto child = children.begin(); child != children.end(); child++) {
					if (!(*child)->empty()) {
						return false;
					}
				}

				return true;
			}
		};
	}
}
