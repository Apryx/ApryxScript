package statement;

import java.util.List;

public class InvokeExpression extends Expression{
	
	private String function;
	private List<Expression> arguments;

	public InvokeExpression(String name, String type, List<Expression> args) {
		super(type);
		this.function = name;
		this.arguments = args;
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
		builder.append("\" type=\"");
		builder.append(type);
		builder.append("\">");
		
		for(Expression e : arguments){
			builder.append(e.toXML());
		}
		
		builder.append("</invoke>");
		
		return builder.toString();
	}
	
}
