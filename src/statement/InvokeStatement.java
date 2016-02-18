package statement;

import java.util.List;

public class InvokeStatement {
	
	private List<Expression> arguments;
	private String function;
	
	//TODO refactor to Function instead of String maybe?
	public InvokeStatement(String function, List<Expression> arguments){
		this.function = function;
		this.arguments = arguments;
	}
	
	public String getFunction() {
		return function;
	}
	
	public List<Expression> getArguments() {
		return arguments;
	}
}
