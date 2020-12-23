#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition()
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;
}

CellPosition::CellPosition(int v, int h)
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition(int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
												// from the passed (cellNum)
												// (*this) = ... --> this will copy the returned (vCell and hCell)
											//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v)
{
	///TODO: Implement this function as described in the .h file (don't forget the validation)
	if (v >= 0 && v <= 8)
	{
		vCell = v;
		return true;
	}
	return false;
	// this line sould be changed with your implementation
}

bool CellPosition::SetHCell(int h)
{
	///TODO: Implement this function as described in the .h file (don't forget the validation)
	if (h >= 0 && h <= 10)
	{
		hCell = h;
		return true;
	}
	return false;

	// this line sould be changed with your implementation
}

int CellPosition::VCell() const
{
	return vCell;
}

int CellPosition::HCell() const
{
	return hCell;
}

bool CellPosition::IsValidCell() const
{
	if (8 >= vCell && vCell >= 0 && hCell >= 0 && hCell <= 10)
	{
		return true;
	}
	else
		return false;

	///TODO: Implement this function as described in the .h file
 // this line sould be changed with your implementation
}

int CellPosition::GetCellNum() const  // this get the cell num by using a function called getcell from position
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum  C1 ,C2 , C3 	
	// which means the object of the current data members (vCell and hCell) "but why we pass the calling object by refrence " ??
}

int CellPosition::GetCellNumFromPosition(const CellPosition& cellPosition)
{
	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it

	///TODO: Implement this function as described in the .h file
	int num;
	return ((cellPosition.HCell() + 1) + (11 * (8 - cellPosition.VCell())));
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;  // create a position from cell position 

	/// TODO: Implement this function as described in the .h file
	if (cellNum % 11 == 0)
		position.SetHCell(10 - cellNum % 11);
	else
		position.SetHCell(cellNum % 11 - 1);
	if (cellNum % 11 == 0)
		position.SetVCell(9 - cellNum / 11);
	else
		position.SetVCell(8 - cellNum / 11);
	return position;


	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it
}

void CellPosition::AddCellNum(int addedNum)
{
	int num = this->GetCellNum() + addedNum;
	/// TODO: Implement this function as described in the .h file
	*this = GetCellPositionFromNum(num);


	// Note: this function updates the data members (vCell and hCell) of the calling object

}