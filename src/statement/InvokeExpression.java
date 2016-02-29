package statement;

import java.util.List;

import ast.ApryxClass;
import ast.Function;
import language.Language;
import tokens.UndefinedReferenceException;

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
	
	@Override
	public void typeCheck(CodeBlock context) {
		//TODO Check arguments invoke!
		
		for(Expression e : arguments){
			e.typeCheck(context);
		}
		
		
		//if the type is unknown, try to find the type
		if(this.getType().equals(Language.TYPE_UNKNOWN)){
			Function f = context.getFunctionByName(function, false);
			
			if(f == null){
				//Might be constructor!
				ApryxClass cls = context.getClassByName(function, false);
				if(cls == null)
					throw new UndefinedReferenceException(function);
				else
					type = cls.getName();
			}
			
			else
				type = f.getType();
		}
	}
	
}
