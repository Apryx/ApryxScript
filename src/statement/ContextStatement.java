package statement;

import context.Context;

public class ContextStatement implements Statement{
	
	private Context context;
	
	public ContextStatement(Context context) {
		this.context = context;
	}
	
	public Context getContext() {
		return context;
	}

	@Override
	public String toJSString() {
		StringBuilder builder = new StringBuilder();
		
		builder.append("{");
		builder.append(context.toJSString());
		builder.append("}");
		
		return builder.toString();
	}
	
	@Override
	public void checkType(Context context) {
		this.context.checkType(context);
	}
	
}
