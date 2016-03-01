package ast;

public class UnknownType extends Type{

	public UnknownType(String name) {
		super(name);
	}
	
	@Override
	public boolean isUnknown() {
		return true;
	}
	
	@Override
	public String toString() {
		return "?" + super.toString();
	}
	
}
