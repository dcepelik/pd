#pragma once

#include "List.hpp"

#include <cassert>

using namespace std;


namespace BoxModel
{
	class VList : public List
	{
	protected:
		double getBoxSize(shared_ptr<Box> box)
		{
			return box->getHeight();
		}


		double getMaxListSize()
		{
			return maxSize;
		}


	public:
		VList(int size) : List(size)
		{
		}


		virtual double getWidth()
		{
			double maxWidth = 0;
			for (auto child: children) {
				maxWidth = max(maxWidth, child->getWidth());
			}

			return maxWidth;
		}


		virtual double getHeight()
		{
			return maxSize;
		}


		void dump(ostream &out, int level)
		{
			out << string(level, '\t') << "^^[" << endl;

			for (auto child: children)
				child->dump(out, level + 1);

			out << string(level, '\t') << ']' << endl;
		}


		void writePSOutput(PS::Writer &writer)
		{
			divideSpaces();

			List::writePSOutput(writer);
			//writer.writeTd(-612, -getMaxListSize());
		}
	};
}
