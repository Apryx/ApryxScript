package statement;

import java.util.List;

@Deprecated
public class InvokeStatement extends Statement{
	
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
	
	public String toXML(){
		/*<invoke name="print" type="void">
			<add type="int">
				<constant type="int">5</constant>
				<constant type="int">3</constant>
			</add>
		</invoke>*/
		
		StringBuilder builder = new StringBuilder();
		
		builder.append("<invoke name=\"");
		builder.append(function);
		
		//void because its not an expression
		builder.append("\" type=\"void\">");
		
		for(Expression e : arguments){
			builder.append(e.toXML());
		}
		
		builder.append("</invoke>");
		
		return builder.toString();
	}
}
