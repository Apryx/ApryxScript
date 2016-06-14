package statement;

import context.Context;
import generation.JSGenerator;

public interface Statement extends JSGenerator{
	public void check(Context context);
}
