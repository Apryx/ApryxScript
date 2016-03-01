package statement;

import java.util.List;
import tokens.UndefinedReferenceException;
import ast.ApryxClass;
import ast.Function;
import ast.Type;

public class InvokeExpression extends Expression{
	
	private String function;
	private List<Expression> arguments;
	private Expression invokationContext;

	public InvokeExpression(String name, Type type, List<Expression> args) {
		super(type);
		this.function = name;
		this.arguments = args;
	}
	
	public InvokeExpression(String name, Type type, List<Expression> args, Expression invokationContext) {
		super(type);
		this.function = name;
		this.arguments = args;
		this.invokationContext = invokationContext;
	}
	
	public void setInvokationContext(Expression invokationContext) {
		this.invokationContext = invokationContext;
	}
	
	public Expression getInvokationContext() {
		return invokationContext;
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
		builder.append("\" static=\"");
		builder.append(invokationContext == null);
		builder.append("\">");
		
		if(invokationContext != null){
			builder.append(invokationContext.toXML());
		}
		
		for(Expression e : arguments){
			builder.append(e.toXML());
		}
		
		builder.append("</invoke>");
		
		return builder.toString();
	}
	
	@Override
	public void typeCheck(Context context) {
		//TODO Check arguments invoke!
		
		for(Expression e : arguments){
			e.typeCheck(context);
		}
		
		//TODO fix
		if(invokationContext == null){
			Function f = context.getFunctionByName(function, false);
			if(f == null)
				throw new UndefinedReferenceException(function);
			
			type = f.getType();
		}else{
			//check the type for the invokation
			invokationContext.typeCheck(context);
			
			Type t = invokationContext.getType();
			
			if(!(t instanceof ApryxClass))
				throw new UndefinedReferenceException(function);
			
			ApryxClass c = (ApryxClass) t;
			
			Function f = c.getBody().getFunctionByName(function, false);
			
			if(f == null)
				throw new UndefinedReferenceException(function);
			
			type = f.getType();
		}
		
	}
	
}
