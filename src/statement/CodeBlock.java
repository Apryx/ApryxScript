package statement;

import java.util.ArrayList;
import java.util.List;

public class CodeBlock extends Statement{
	
	private CodeBlock parent;
	private List<Statement> statements;
	
	public CodeBlock(){
		this(null);
	}
	
	public CodeBlock(CodeBlock parent){
		this.parent = parent;
		statements = new ArrayList<Statement>();
	}
	
	public void add(Statement statement){
		this.statements.add(statement);
	}
	
	public CodeBlock getParent() {
		return parent;
	}
	
	public DeclareStatement getVariableByName(String name, boolean local){
		for(Statement s : statements){
			if(s instanceof DeclareStatement){
				DeclareStatement d = (DeclareStatement) s;
				
				if(d.getName().equals(name))
					return d;
			}
		}
		if(!local && parent != null)
			return parent.getVariableByName(name, local);
		
		return null;
	}
	
	@Override
	public String toString() {
		return statements.toString();
	}
	
	public String toXML(){
		StringBuilder builder = new StringBuilder();
		
		for(Statement s : statements){
			builder.append(s.toXML());
		}
		
		return builder.toString();
	}
}
