// 2017-03-30T10:08+08:00
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.Diagnostics;
using System.Drawing;
using System.Linq;


namespace LayoutAlg
{
    public abstract class CompositeElementBase : ElementBase
    {
        public readonly ObservableCollection<ElementBase> Children;

        public CompositeElementBase()
        {
            Children = new ObservableCollection<ElementBase>();
            Children.CollectionChanged += OnChildrenCollectionChanged;
        }

        public IEnumerable<ElementBase> GetElements(bool skipCompositeElement = true)
        {
            return skipCompositeElement ? GetElements(this, skipCompositeElement) : 
                new ElementBase[1] { this }.Concat(GetElements(this, skipCompositeElement));
        }

        public IEnumerable<T> GetElements<T>(bool skipCompositeElement = true) where T : ElementBase
        {
            return GetElements(skipCompositeElement).OfType<T>();
        }

        public override void Draw(Graphics graphics)
        {
            foreach (var child in Children)
                child.Draw(graphics);
        }
        

        private static IEnumerable<ElementBase> GetElements(CompositeElementBase root, bool skipCompositeElement = true)
        {
            Debug.Assert(root != null);

            foreach (var element in root.Children)
            {
                if (element != null)
                {
                    var compositeElement = element as CompositeElementBase;
                    if (compositeElement != null)
                    {
                        if (!skipCompositeElement)
                            yield return compositeElement;

                        foreach (var subElement in GetElements(compositeElement, skipCompositeElement))
                            yield return subElement;
                    }
                    else
                    {
                        yield return element;
                    }
                }
            }
        }

        private void OnChildrenCollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            OnLayoutChanged(new LayoutChangedEventArgs(Bounds));

            switch (e.Action)
            {
                case NotifyCollectionChangedAction.Add:
                    foreach (var child in e.NewItems.Cast<ElementBase>())
                    {
                        Debug.Assert(child != null);
                    }
                    break;
                case NotifyCollectionChangedAction.Remove:
                    foreach (var child in e.OldItems.Cast<ElementBase>())
                    {
                        Debug.Assert(child != null);
                    }
                    break;
            }
        }
    }
}
