package statement;

import context.Context;
import generation.JSGenerator;

public abstract class Expression implements JSGenerator{
	public abstract void check(Context context);
}
