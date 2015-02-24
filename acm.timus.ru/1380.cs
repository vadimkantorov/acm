using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;

class Program
{
	static void Main(string[] args)
	{
		//new Program().Run(Console.In, Console.Out);
		new Program().Run(new StreamReader("input.txt"), Console.Out);
	}

	void Run(TextReader input, TextWriter output)
	{
		var ser = new BoardSerializer();
		var brd = ser.Deserialize(input);
		int p = Convert.ToInt32(input.ReadLine());
		var currentColor = (ChessColor) Enum.Parse(typeof (ChessColor), input.ReadLine());
		for(int i = 0; i < p; i++)
		{
			var crds = input.ReadLine().Split('-').Select(x => new {h = x[0] - 'a', v = x[1] - '1'}).ToArray();
			var outcome = brd.SmellMove(currentColor,crds[0].h, crds[0].v, crds[1].h, crds[1].v);
			output.WriteLine(outcome);


			if (outcome != MoveSmell.Incorrect)
			{
				brd.PerformMove(crds[0].h, crds[0].v, crds[1].h, crds[1].v);
				currentColor = currentColor.Switch();
			}

			if (outcome == MoveSmell.Draw || outcome == MoveSmell.Incorrect || outcome == MoveSmell.Mate)
				break;
		}

		output.WriteLine();
		ser.Serialize(brd, output);
	}
}

class Board
{
	public const int Size = 8;

	MoveSmell SmellMoveWeak(ChessColor color, int h1, int v1, int h2, int v2)
	{
		if (h1 == h2 && v1 == v2)
			return MoveSmell.Incorrect;
		if (m[h1, v1] == null || m[h1, v1].Color != color || m[h2, v2] != null && m[h2, v2].Color == color)
			return MoveSmell.Incorrect;

		return m[h1, v1].CanMove(h1, v1, h2, v2, this) ? MoveSmell.Correct : MoveSmell.Incorrect;
	}
	
	public MoveSmell SmellMove(ChessColor color, int h1, int v1, int h2, int v2)
	{
		if(SmellMoveWeak(color, h1, v1, h2, v2) == MoveSmell.Incorrect)
			return MoveSmell.Incorrect;

		using (TempMove(h1, v1, h2, v2))
		{
			if (IsUnderCheck(color))
				return MoveSmell.Incorrect;

			if (IsUnderCheck(color.Switch()))
			{
				if (!MovesExist(color.Switch()))
					return MoveSmell.Mate;
				return MoveSmell.Check;
			}
			else if (!MovesExist(color.Switch()))
				return MoveSmell.Draw;

			return MoveSmell.Correct;
		}
	}

	bool IsUnderCheck(ChessColor color)
	{
		for(int i = 0; i < Size; i++)
			for (int j = 0; j < Size; j++)
				for (int i_ = 0; i_ < Size; i_++)
					for (int j_ = 0; j_ < Size; j_++)
						if (m[i,j] is King && m[i,j].Color == color && SmellMoveWeak(color.Switch(), i_, j_, i, j) == MoveSmell.Correct)
							return true;
		return false;
	}

	bool MovesExist(ChessColor color)
	{
		for(int i = 0; i < Size; i++)
			for (int j = 0; j < Size; j++)
				for(int i_ = 0; i_ < Size; i_++)
					for(int j_ = 0; j_ < Size; j_++)
						if (SmellMoveWeak(color, i, j, i_, j_) == MoveSmell.Correct)// && !(m[i_,j_] is King))
						{
							using (TempMove(i, j, i_, j_))
								if (!IsUnderCheck(color))
									return true;
						}

		return false;
	}

	public void PerformMove(int h1, int v1, int h2, int v2)
	{
		m[h2, v2] = m[h1, v1];
		m[h1, v1] = null;
	}

	public Figure this[int i, int j]
	{
		get { return m[i,j]; }
		set { m[i, j] = value; }
	}

	IDisposable TempMove(int h1, int v1, int h2, int v2)
	{
		return new DisposableMove(this, h1, v1, h2, v2);
	}

	class DisposableMove : IDisposable
	{
		public DisposableMove(Board brd, int h1, int v1, int h2, int v2)
		{
			this.h1 = h1;
			this.v1 = v1;
			this.h2 = h2;
			this.v2 = v2;
			this.brd = brd;

			oldFig = brd[h2, v2];
			brd.PerformMove(h1, v1, h2, v2);
		}

		public void Dispose()
		{
			brd.PerformMove(h2, v2, h1, v1);
			brd[h2, v2] = oldFig;
		}

		readonly Board brd;
		readonly int h1, h2, v1, v2;
		readonly Figure oldFig;
	}

	readonly Figure[,] m = new Figure[Size,Size];
}

class BoardSerializer
{
	public Board Deserialize(TextReader input)
	{
		var res = new Board();
		for (int i = 0; i < Board.Size; i++)
		{
			var integers = input.ReadLine().Trim().Split().Select(x => Convert.ToInt32(x)).ToArray();
			for (int j = 0; j < Board.Size; j++)
			{
				res[j, Board.Size-i-1] = FigureExtensions.FromInteger(integers[j]);
			}
		}
		return res;
	}

	public void Serialize(Board brd, TextWriter output)
	{
		for (int i = Board.Size-1; i >= 0; i--)
		{
			for (int j = 0; j < Board.Size; j++)
			{
				output.Write(brd[j, i].ToInteger());
				output.Write(" ");
			}
			output.WriteLine();
		}
	}
}

class Figure
{
	public ChessColor Color { get; set; }

	public virtual bool CanMove(int h1, int v1, int h2, int v2, Board brd)
	{
		return brd[h2, v2] == null || brd[h2, v2].Color != Color;
	}
}

[FigureValue(1)]
class Pawn : LineFigure
{
	public override bool CanMove(int h1, int v1, int h2, int v2, Board brd)
	{
		if (!base.CanMove(h1, v1, h2, v2, brd))
			return false;

		if (Color == ChessColor.White && v2 - v1 < 0)
			return false;
		if (Color == ChessColor.Black && v2 - v1 > 0)
			return false;

		int dh = Math.Abs(h2 - h1);
		int dv = Math.Abs(v2 - v1);

		if (dh > 1 || dv > 2)
			return false;
		
		if (dh == 1)
			return dv == 1 && brd[h2, v2] != null;
		else// if(dh == 0)
			return brd[h2, v2] == null && (dv == 2 ? v1 == 1 || v1 == 6 : true);

			
	}
}

[FigureValue(2)]
class Knight : Figure
{
	public override bool CanMove(int h1, int v1, int h2, int v2, Board brd)
	{
		if (!base.CanMove(h1, v1, h2, v2, brd))
			return false;

		int dh = Math.Abs(h2 - h1);
		int dv = Math.Abs(v2 - v1);
		return dh + dv == 3 && dh < 3 && dv < 3;
	}
}

class LineFigure : Figure
{
	public override bool CanMove(int h1, int v1, int h2, int v2, Board brd)
	{
		if(!base.CanMove(h1, v1, h2, v2, brd))
			return false;

		if (!(h1 == h2 || v1 == v2 || Math.Abs(v2 - v1) == Math.Abs(h2 - h1)))
			return false;
		
		int dh = h1 < h2 ? 1 : h1 > h2 ? -1 : 0;
		int dv = v1 < v2 ? 1 : v1 > v2 ? -1 : 0;

		for (int h = h1+dh, v = v1+dv; h != h2 || v != v2; h += dh, v += dv)
			if (brd[h, v] != null)
				return false;

		return true;
	}
}

[FigureValue(3)]
class Bishop : LineFigure
{
	public override bool CanMove(int h1, int v1, int h2, int v2, Board brd)
	{
		if (!base.CanMove(h1, v1, h2, v2, brd))
			return false;
		return Math.Abs(v2 - v1) == Math.Abs(h2 - h1);
	}
}

[FigureValue(4)]
class Rook : LineFigure
{
	public override bool CanMove(int h1, int v1, int h2, int v2, Board brd)
	{
		if (!base.CanMove(h1, v1, h2, v2, brd))
			return false;
		return h1 == h2 || v1 == v2;
	}
}

[FigureValue(5)]
class Queen : Figure
{
	public override bool CanMove(int h1, int v1, int h2, int v2, Board brd)
	{
		if (!base.CanMove(h1, v1, h2, v2, brd))
			return false;
		return new Rook{Color = Color}.CanMove(h1, v1, h2, v2, brd) || new Bishop {Color = Color}.CanMove(h1, v1, h2, v2, brd);
	}
}

[FigureValue(6)]
class King : Figure
{
	public override bool CanMove(int h1, int v1, int h2, int v2, Board brd)
	{
		if (!base.CanMove(h1, v1, h2, v2, brd))
			return false;
		return Math.Abs(h2 - h1) <= 1 && Math.Abs(v2 - v1) <= 1;
	}
}

enum MoveSmell
{
	Correct,
	Incorrect,
	Check,
	Mate,
	Draw
}

class FigureValueAttribute :Attribute
{
	public FigureValueAttribute(int value)
	{
		Value = value;
	}

	public int Value { get; private set; }
}

enum ChessColor
{
	White,
	Black
}

static class ChessColorExtensions
{
	public static ChessColor Switch(this ChessColor color)
	{
		return color == ChessColor.Black ? ChessColor.White : ChessColor.Black;
	}
}



static class FigureExtensions
{
	public static Figure FromInteger(int x)
	{
		if(x == 0)
			return null;

		var res = constructors[Math.Abs(x)]();
		if (x < 0)
			res.Color = ChessColor.Black;
		return res;
	}

	public static int ToInteger(this Figure x)
	{
		if (x == null)
			return 0;
		int res = Value(x.GetType()).Value;
		return x.Color == ChessColor.White ? res : -res;
	}

	static FigureExtensions()
	{
		constructors = Assembly
			.GetExecutingAssembly()
			.GetTypes()
			.Select(x => new {Type = x, Value = Value(x)})
			.Where(x => x.Value != null)
			.ToDictionary(x => x.Value.Value, x => (Func<Figure>)(() => (Figure)Activator.CreateInstance(x.Type)));
	}

	static int? Value(Type maybeFigure)
	{
		return maybeFigure
			.GetCustomAttributes(typeof(FigureValueAttribute), true)
			.Cast<FigureValueAttribute>()
			.Select(x => x.Value)
			.Cast<int?>()
			.FirstOrDefault();
	}

	static readonly IDictionary<int, Func<Figure>> constructors;
}