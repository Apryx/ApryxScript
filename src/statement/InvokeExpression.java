package statement;

import java.util.List;

public class InvokeExpression extends Expression{
	
	private Expression invoke;
	private List<Expression> arguments;
	
	public InvokeExpression(Expression invoke, List<Expression> arguments){
		this.invoke = invoke;
		this.arguments = arguments;
	}
	
	public List<Expression> getArguments() {
		return arguments;
	}
	
	public Expression getInvoke() {
		return invoke;
	}

	@Override
	public String toJSString() {
		StringBuilder builder = new StringBuilder();
		
		builder.append(invoke.toJSString());
		
		builder.append('(');
		
		for(int i = 0; i < arguments.size(); i++){
			builder.append(arguments.get(i).toJSString());
			if(i != arguments.size() - 1)
				builder.append(", ");
		}
		
		builder.append(')');
		
		return builder.toString();
	}
}
