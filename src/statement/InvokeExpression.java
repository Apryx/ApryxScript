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
}
