package ast;

public class ClassType extends Type{

	public ClassType(String name) {
		super(name);
	}
	
	@Override
	public boolean isInvokeable() {
		return false;
	}
	
}
